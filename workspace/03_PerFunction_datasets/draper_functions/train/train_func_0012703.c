alc_process_coef_fw(struct hda_codec *codec,
				const struct coef_fw *fw)
{
	for (; fw->nid; fw++) {
		if (fw->mask == (unsigned short)-1)
			alc_write_coefex_idx(codec, fw->nid, fw->idx, fw->val);
		else
			alc_update_coefex_idx(codec, fw->nid, fw->idx,
					      fw->mask, fw->val);
	}
}
