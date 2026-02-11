radd_std_star(struct vs_recipy *vs, char *val)
{
	char ras[64];
	char decs[64];
	float x,y,smag;
	double ra, dec = 0.0;
	int ret;

	if (vs->cnt >= vs->max_cnt) {
		err_printf("More than %d stars in recipy, ignoring\n", vs->max_cnt);
		return -1;
	}

	if (vs->usewcs) {
		ret = sscanf(val, "%s %s %f", ras, decs, &smag);
		if (ret != 3) {
			err_printf("malformed ra/dec/mag std star line:    \n%s\n", val);
			return -1;
		}
		ret = scan_ra(&ra, ras);
		if (ret < 0)
			return ret;
		ret = scan_dec(&ra, decs);
		if (ret < 0)
			return ret;

		vs->s[vs->cnt].ra = ra;
		vs->s[vs->cnt].dec = dec;
		vs->s[vs->cnt].aph.stdmag = smag;
		vs->s[vs->cnt].aph.flags |= AP_STD_STAR;
		vs->cnt ++;
	} else {
		ret = sscanf(val, "%f %f %f", &x, &y, &smag);
		if (ret != 3) {
			err_printf("malformed x/y/mag std star line:\n    %s\n", val);
			return -1;
		}

		vs->s[vs->cnt].x = x;
		vs->s[vs->cnt].y = y;
		vs->s[vs->cnt].aph.stdmag = smag;
		vs->s[vs->cnt].aph.flags |= AP_STD_STAR;
		vs->cnt ++;
	}
	return 0;
}
