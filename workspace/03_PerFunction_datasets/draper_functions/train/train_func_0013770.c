gen_write_label (parser *p, int oldv)
{
    char tmp[MAXLABEL];
    const char *src = "";
    size_t len = 0;

    if (p->targ != VEC) {

	return;
    }

    if (p->lh.substr != NULL) {


	return;
    }

    maybe_record_lag_info(p);

    *tmp = '\0';

    if (p->lh.v < oldv && p->targ == VEC) {
	int m = get_model_count();

	if (m > 0) {
	    sprintf(tmp, _("Replaced after model %d: "), m);
	    len = strlen(tmp);
	}
    }

    if (*p->lh.label != '\0' && (p->flags & P_UFRET)) {
	src = p->lh.label;
    } else if (*p->lh.label != '\0' && dollar_node(p->tree)) {
	src = p->lh.label;
    } else if (p->rhs != NULL && strcmp(p->rhs, "NA")) {
	src = p->rhs;
    }

    if (strlen(src) > MAXLABEL - 1 - len) {
	strncat(tmp, src, MAXLABEL - 4 - len);
	strcat(tmp, "...");
    } else {
	strncat(tmp, src, MAXLABEL - 1);
    }

    series_set_label(p->dset, p->lh.v, tmp);
    series_set_flag(p->dset, p->lh.v, VAR_GENERATED);

#if GDEBUG
    fprintf(stderr, "varlabel: '%s'\n", series_get_label(p->dset, p->lh.v));
#endif
}
