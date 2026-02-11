XGIfb_search_vesamode(struct xgifb_video_info *xgifb_info,
				  unsigned int vesamode)
{
	int i = 0;

	if (vesamode == 0)
		goto invalid;

	vesamode &= 0x1dff;

	while (XGIbios_mode[i].mode_no != 0) {
		if ((XGIbios_mode[i].vesa_mode_no_1 == vesamode) ||
		    (XGIbios_mode[i].vesa_mode_no_2 == vesamode)) {
			xgifb_info->mode_idx = i;
			return;
		}
		i++;
	}

invalid:
	pr_info("Invalid VESA mode 0x%x'\n", vesamode);
}
