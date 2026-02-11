efx_mcdi_read_response_header(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	unsigned int respseq, respcmd, error;
#ifdef CONFIG_SFC_MCDI_LOGGING
	char *buf = mcdi->logging_buffer;
#endif
	efx_dword_t hdr;

	efx->type->mcdi_read_response(efx, &hdr, 0, 4);
	respseq = EFX_DWORD_FIELD(hdr, MCDI_HEADER_SEQ);
	respcmd = EFX_DWORD_FIELD(hdr, MCDI_HEADER_CODE);
	error = EFX_DWORD_FIELD(hdr, MCDI_HEADER_ERROR);

	if (respcmd != MC_CMD_V2_EXTN) {
		mcdi->resp_hdr_len = 4;
		mcdi->resp_data_len = EFX_DWORD_FIELD(hdr, MCDI_HEADER_DATALEN);
	} else {
		efx->type->mcdi_read_response(efx, &hdr, 4, 4);
		mcdi->resp_hdr_len = 8;
		mcdi->resp_data_len =
			EFX_DWORD_FIELD(hdr, MC_CMD_V2_EXTN_IN_ACTUAL_LEN);
	}

#ifdef CONFIG_SFC_MCDI_LOGGING
	if (mcdi->logging_enabled && !WARN_ON_ONCE(!buf)) {
		size_t hdr_len, data_len;
		int bytes = 0;
		int i;

		WARN_ON_ONCE(mcdi->resp_hdr_len % 4);
		hdr_len = mcdi->resp_hdr_len / 4;


		data_len = DIV_ROUND_UP(mcdi->resp_data_len, 4);


		for (i = 0; i < hdr_len && bytes < PAGE_SIZE; i++) {
			efx->type->mcdi_read_response(efx, &hdr, (i * 4), 4);
			bytes += snprintf(buf + bytes, PAGE_SIZE - bytes,
					  " %08x", le32_to_cpu(hdr.u32[0]));
		}

		for (i = 0; i < data_len && bytes < PAGE_SIZE; i++) {
			efx->type->mcdi_read_response(efx, &hdr,
					mcdi->resp_hdr_len + (i * 4), 4);
			bytes += snprintf(buf + bytes, PAGE_SIZE - bytes,
					  " %08x", le32_to_cpu(hdr.u32[0]));
		}

		netif_info(efx, hw, efx->net_dev, "MCDI RPC RESP:%s\n", buf);
	}
#endif

	if (error && mcdi->resp_data_len == 0) {
		netif_err(efx, hw, efx->net_dev, "MC rebooted\n");
		mcdi->resprc = -EIO;
	} else if ((respseq ^ mcdi->seqno) & SEQ_MASK) {
		netif_err(efx, hw, efx->net_dev,
			  "MC response mismatch tx seq 0x%x rx seq 0x%x\n",
			  respseq, mcdi->seqno);
		mcdi->resprc = -EIO;
	} else if (error) {
		efx->type->mcdi_read_response(efx, &hdr, mcdi->resp_hdr_len, 4);
		mcdi->resprc =
			efx_mcdi_errno(EFX_DWORD_FIELD(hdr, EFX_DWORD_0));
	} else {
		mcdi->resprc = 0;
	}
}
