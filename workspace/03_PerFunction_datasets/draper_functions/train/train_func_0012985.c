detect_guide_star(struct ccd_frame *fr, struct region *reg)
{
	struct gui_star *gs;
	struct sources *src;
 	double score, max_score = 0;
	int gsi = 0, i = 0;
	double xc, yc, rf, ds;
	double ref_flux = 0.0, ref_fwhm = 0.0;

	src = new_sources(P_INT(SD_MAX_STARS));
	if (src == NULL) {
		err_printf("detect_guide_star: cannot create sources\n");
		return NULL;
	}
	rf = (fr->w * fr->w + fr->h * fr->h) / PI / 2;
	xc = fr->w / 2;
	yc = fr->h / 2;
	extract_stars(fr, reg, 0, P_DBL(SD_SNR), src);
	if (src->ns <= 0)
		return NULL;
	for (i = 0; i < src->ns; i++) {
		if (src->s[i].peak > P_DBL(AP_SATURATION))
			continue;
		ref_flux = src->s[i].flux;
		ref_fwhm = src->s[i].fwhm;
		break;
	}
	for (i = 0; i < src->ns; i++) {
		if (src->s[i].peak > P_DBL(AP_SATURATION))
			continue;
		xc = cos((src->s[i].x - fr->w / 2) / fr->w * PI);
		yc = cos((src->s[i].y - fr->h / 2) / fr->h * PI);
		ds = sqr(xc * yc);
		score = src->s[i].flux * ds;
		d3_printf("%5.1f %5.1f ds: %.3f score: %.1f\n",
			  src->s[i].x, src->s[i].y, ds, score);
		if (score > max_score) {
			max_score = score;
			gsi = i;
		}
	}
	gs = gui_star_new();
	gs->x = src->s[gsi].x;
	gs->y = src->s[gsi].y;
	gs->size = 1.0 * P_INT(DO_DEFAULT_STAR_SZ);
	gs->flags = STAR_TYPE_ALIGN;
	gs->s = (struct star *)g_malloc(sizeof(struct star));
	*STAR(gs->s) = src->s[gsi];
	STAR(gs->s)->ref_count = 1;
	release_sources(src);

	return gs;
}
