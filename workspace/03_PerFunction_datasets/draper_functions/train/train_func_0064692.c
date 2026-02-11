ndmp_9to3_device_info_vec_dup (
  ndmp9_device_info *devinf9,
  ndmp3_device_info **devinf3_p,
  int n_devinf)
{
	ndmp3_device_info *	devinf3;
	int			i;
	unsigned int		j;

	devinf3 = *devinf3_p = NDMOS_MACRO_NEWN(ndmp3_device_info, n_devinf);
	if (!devinf3) {
		return -1;
	}

	for (i = 0; i < n_devinf; i++) {
		ndmp9_device_info *	di9 = &devinf9[i];
		ndmp3_device_info *	di3 = &devinf3[i];

		NDMOS_MACRO_ZEROFILL (di3);

		CNVT_STRDUP_FROM_9 (di3, di9, model);

		di3->caplist.caplist_val =
			NDMOS_MACRO_NEWN (ndmp3_device_capability,
				di9->caplist.caplist_len);

		if (!di3->caplist.caplist_val) {
			return -1;
		}

		for (j = 0; j < di9->caplist.caplist_len; j++) {
			ndmp9_device_capability *	cap9;
			ndmp3_device_capability *	cap3;

			cap9 = &di9->caplist.caplist_val[j];
			cap3 = &di3->caplist.caplist_val[j];

			NDMOS_MACRO_ZEROFILL (cap3);

			CNVT_STRDUP_FROM_9 (cap3, cap9, device);

			ndmp_9to3_pval_vec_dup (
				cap9->capability.capability_val,
				&cap3->capability.capability_val,
				cap9->capability.capability_len);

			cap3->capability.capability_len =
				cap9->capability.capability_len;
		}
		di3->caplist.caplist_len = j;
	}

	return 0;
}
