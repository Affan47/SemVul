seriesobject_or_id(struct finfo *f, Object *o, char *what, int *which,
		   int enumval, int *skip)
{
    int rc;
    int value;
    int objtype;
    int start;
    struct getby *gp;

    *which = f->activity;

    rc = parse_objectid(f, &value, &objtype, what);
    if (!rc)
	return ERROR;

    gp = &(f->gb);


    if (gp->seriesflag != 0) {
	if (gp->seriesflag & SL_START) {
	    start = gp->serieslim[0];
	    if (start > enumval) {
		*skip = 1;
		return OK;
	    }
	} else
	    start = 0;

	if (gp->seriesflag & SL_END) {
	    if (gp->serieslim[1] < enumval) {
		*skip = 1;
		return OK;
	    }
	}

	if (gp->seriesflag & SL_DELTA) {
	    if ((enumval - start) % gp->serieslim[2]) {
		*skip = 1;
		return OK;
	    }
	}
    }

    *skip = 0;

    if (*which == IDENTIFY_OBJS) {
	rc =  _dxfobjusesobj(f, f->curid, value);
	if (!rc) {
	    DXSetError(ERROR_DATA_INVALID, "bad or missing %s object", what);
	    return ERROR;
	}
    }
    else {
	if (objtype == ID_LOCAL)
	    rc = _dxflookobjlist(f, value, o, NULL);
	else
	    rc = remote_object(f, value, o);

	if (!rc || !*o) {
	    DXSetError(ERROR_DATA_INVALID, "bad or missing %s object", what);
	    return ERROR;
	}
    }

    return rc;
}
