brcmf_fil_bsscfg_data_get(struct brcmf_if *ifp, char *name,
			  void *data, u32 len)
{
	struct brcmf_pub *drvr = ifp->drvr;
	s32 err;
	u32 buflen;

	mutex_lock(&drvr->proto_block);

	buflen = brcmf_create_bsscfg(ifp->bssidx, name, data, len,
				     drvr->proto_buf, sizeof(drvr->proto_buf));
	if (buflen) {
		err = brcmf_fil_cmd_data(ifp, BRCMF_C_GET_VAR, drvr->proto_buf,
					 buflen, false);
		if (err == 0)
			memcpy(data, drvr->proto_buf, len);
	} else {
		err = -EPERM;
		brcmf_err("Creating bsscfg failed\n");
	}
	brcmf_dbg(FIL, "ifidx=%d, bssidx=%d, name=%s, len=%d\n", ifp->ifidx,
		  ifp->bssidx, name, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uint, len, MAX_HEX_DUMP_LEN), "data\n");

	mutex_unlock(&drvr->proto_block);
	return err;

}
