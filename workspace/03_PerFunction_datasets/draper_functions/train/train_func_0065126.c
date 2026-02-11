diff_grep(struct diff_filepair *p, regex_t *regexp, struct diff_options *o)
{
	regmatch_t regmatch;
	struct userdiff_driver *textconv_one = NULL;
	struct userdiff_driver *textconv_two = NULL;
	mmfile_t mf1, mf2;
	int hit;

	if (diff_unmodified_pair(p))
		return 0;

	fill_one(p->one, &mf1, &textconv_one);
	fill_one(p->two, &mf2, &textconv_two);

	if (!mf1.ptr) {
		if (!mf2.ptr)
			return 0;

		hit = !regexec(regexp, p->two->data, 1, &regmatch, 0);
	} else if (!mf2.ptr) {

		hit = !regexec(regexp, p->one->data, 1, &regmatch, 0);
	} else {


		struct diffgrep_cb ecbdata;
		xpparam_t xpp;
		xdemitconf_t xecfg;

		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		ecbdata.regexp = regexp;
		ecbdata.hit = 0;
		xecfg.ctxlen = o->context;
		xecfg.interhunkctxlen = o->interhunkcontext;
		xdi_diff_outf(&mf1, &mf2, diffgrep_consume, &ecbdata,
			      &xpp, &xecfg);
		hit = ecbdata.hit;
	}
	if (textconv_one)
		free(mf1.ptr);
	if (textconv_two)
		free(mf2.ptr);
	return hit;
}
