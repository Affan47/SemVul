nut_find_infoval(info_lkp_t *xcp2info, const double value)
{
	info_lkp_t	*info_lkp;


	if (xcp2info->fun != NULL) {
		return xcp2info->fun(value);
	}


	for (info_lkp = xcp2info; info_lkp->nut_value != NULL; info_lkp++) {
		if (info_lkp->xcp_value == (long)value) {
			upsdebugx(5, "nut_find_infoval: found %s (value: %ld)", info_lkp->nut_value, (long)value);
			return info_lkp->nut_value;
		}
	}

	upsdebugx(3, "hu_find_infoval: no matching INFO_* value for this XCP value (%g)", value);
	return NULL;
}
