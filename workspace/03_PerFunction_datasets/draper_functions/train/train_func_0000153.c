dw_mci_translate_sglist(struct dw_mci *host, struct mmc_data *data,
				    unsigned int sg_len)
{
	unsigned int desc_len;
	int i;

	if (host->dma_64bit_address == 1) {
		struct idmac_desc_64addr *desc_first, *desc_last, *desc;

		desc_first = desc_last = desc = host->sg_cpu;

		for (i = 0; i < sg_len; i++) {
			unsigned int length = sg_dma_len(&data->sg[i]);

			u64 mem_addr = sg_dma_address(&data->sg[i]);

			for ( ; length ; desc++) {
				desc_len = (length <= DW_MCI_DESC_DATA_LENGTH) ?
					   length : DW_MCI_DESC_DATA_LENGTH;

				length -= desc_len;


				desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC |
							IDMAC_DES0_CH;


				IDMAC_64ADDR_SET_BUFFER1_SIZE(desc, desc_len);


				desc->des4 = mem_addr & 0xffffffff;
				desc->des5 = mem_addr >> 32;


				mem_addr += desc_len;


				desc_last = desc;
			}
		}


		desc_first->des0 |= IDMAC_DES0_FD;


		desc_last->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
		desc_last->des0 |= IDMAC_DES0_LD;

	} else {
		struct idmac_desc *desc_first, *desc_last, *desc;

		desc_first = desc_last = desc = host->sg_cpu;

		for (i = 0; i < sg_len; i++) {
			unsigned int length = sg_dma_len(&data->sg[i]);

			u32 mem_addr = sg_dma_address(&data->sg[i]);

			for ( ; length ; desc++) {
				desc_len = (length <= DW_MCI_DESC_DATA_LENGTH) ?
					   length : DW_MCI_DESC_DATA_LENGTH;

				length -= desc_len;


				desc->des0 = cpu_to_le32(IDMAC_DES0_OWN |
							 IDMAC_DES0_DIC |
							 IDMAC_DES0_CH);


				IDMAC_SET_BUFFER1_SIZE(desc, desc_len);


				desc->des2 = cpu_to_le32(mem_addr);


				mem_addr += desc_len;


				desc_last = desc;
			}
		}


		desc_first->des0 |= cpu_to_le32(IDMAC_DES0_FD);


		desc_last->des0 &= cpu_to_le32(~(IDMAC_DES0_CH |
					       IDMAC_DES0_DIC));
		desc_last->des0 |= cpu_to_le32(IDMAC_DES0_LD);
	}

	wmb();
}
