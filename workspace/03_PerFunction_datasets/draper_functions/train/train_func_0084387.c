gen_special (const char *s, const char *line,
			DATASET *dset, PRN *prn, parser *p)
{
    const char *msg = NULL;
    int orig_v = dset->v;
    int write_label = 0;
    int err = 0;

    if (dset == NULL || dset->n == 0) {
	return E_NODATA;
    }

    if (!strcmp(s, "markers")) {
	return generate_obs_markers(line, dset);
    } else if (!strcmp(s, "dummy")) {
	int di0 = dummy(dset, 0);

	if (di0 == 0) {
	    err = 1;
	} else {
	    if (di0 == orig_v) {
		msg = N_("Periodic dummy variables generated.\n");
	    } else {
		msg = N_("Periodic dummy variables already present.\n");
	    }
	}
    } else if (!strcmp(s, "timedum")) {
	err = panel_dummies(dset, OPT_T, prn);
	if (!err) {
	    msg = N_("Panel dummy variables generated.\n");
	}
    } else if (!strcmp(s, "unitdum")) {
	err = panel_dummies(dset, OPT_NONE, prn);
	if (!err) {
	    msg = N_("Panel dummy variables generated.\n");
	}
    } else if (!strcmp(s, "time")) {
	err = gen_time(dset, 1);
	write_label = 1;
    } else if (!strcmp(s, "index")) {
	err = gen_time(dset, 0);
	write_label = 1;
    } else if (!strcmp(s, "unit")) {
	err = gen_unit(dset);
	write_label = 1;
    } else if (!strcmp(s, "weekday")) {
	err = gen_wkday(dset);
	write_label = 1;
    }

    if (msg != NULL && gretl_messages_on()) {
	pputs(prn, _(msg));
    }

    if (!err && write_label) {
	strcpy(p->lh.name, s);
	p->lh.v = series_index(dset, s);
	p->dset = dset;
	p->targ = VEC;
	p->flags = 0;
	p->err = 0;
	p->prn = prn;
	gen_write_message(p, orig_v, prn);
    }

    if (dset->v > orig_v) {
	set_dataset_is_changed();
	genr_last_type = GRETL_TYPE_SERIES;
    }

    return err;
}
