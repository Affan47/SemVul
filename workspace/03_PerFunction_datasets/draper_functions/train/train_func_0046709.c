brcmf_fil_bsscfg_int_get(struct brcmf_if *ifp, char *name, u32 *data)
{
	__le32 data_le = cpu_to_le32(*data);
	s32 err;

	err = brcmf_fil_bsscfg_data_get(ifp, name, &data_le,
					sizeof(data_le));
	if (err == 0)
		*data = le32_to_cpu(data_le);
	return err;
}
