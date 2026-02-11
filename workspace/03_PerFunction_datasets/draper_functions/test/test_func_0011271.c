do_stack_time(struct image_file_list *imfl, struct ccd_frame *ofr,
			int (* progress)(char *msg, void *data), void *data)
{
	int i;
	GList *gl;
	struct image_file *imf;
	double expsum = 0.0;
	double exptime = 0.0;
	double jd, v;
	char lb[128];
	char date[64];

	gl = imfl->imlist;
	i=0;
	while (gl != NULL) {
		imf = gl->data;
		gl = g_list_next(gl);
		if (imf->flags & IMG_SKIP)
			continue;
		if (i >= COMB_MAX) {
			d1_printf("reached stacking limit\n");
			break;
		}
		i++;
		jd = frame_jdate(imf->fr);
		if (jd == 0) {
			if (progress) {
				(*progress)("stack_time: bad time, skipping frame\n",
					    data);
			}
			continue;
		}
		if (fits_get_double(imf->fr, P_STR(FN_EXPTIME), &v) > 0) {
			d1_printf("stack time: using exptime = %.3f from %s\n",
				  v, P_STR(FN_EXPTIME));
		} else {
			v = 0.0;
			if (progress) {
				(*progress)("stack_time: bad exptime, skipping frame\n",
					    data);
			}
			continue;
		}
		expsum += v;
		exptime += (jd + v /2/24/3600) * v;
	}
	if (expsum == 0)
		return 0;
	if (progress) {
		snprintf(lb, 79, "eqivalent exp: %.1fs, center at jd:%.7f\n",
			 expsum, exptime/expsum);
		(*progress)(lb, data);
	}
	sprintf(lb, "%20.3f / EXPOSURE TIME IN SECONDS", expsum);
	fits_add_keyword(ofr, P_STR(FN_EXPTIME), lb);
	sprintf(lb, "%20.8f / JULIAN DATE OF EXPOSURE START (UTC)",
		exptime/expsum - expsum/2/24/3600);
	fits_add_keyword(ofr, P_STR(FN_JDATE), lb);
	date_time_from_jdate(exptime/expsum - expsum/2/24/3600, date, 63);
	fits_add_keyword(ofr, P_STR(FN_DATE_OBS), date);
	fits_delete_keyword(ofr, P_STR(FN_MJD));
	fits_delete_keyword(ofr, P_STR(FN_TIME_OBS));
	return 0;
}
