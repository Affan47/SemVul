find_smatch (const char *oname)
{
    stacker *smatch = NULL;

    if (oname == NULL || *oname == '\0') {
	if (genr_model.ptr != NULL) {
	    smatch = &genr_model;
	} else {
	    smatch = &last_model;
	}
    } else {
	const char *test;
	int i;

	for (i=0; i<n_obj; i++) {
	    test = gretl_object_get_name(ostack[i].ptr, ostack[i].type);
	    if (!strcmp(oname, test)) {
		smatch = &ostack[i];
		break;
	    }
	}
    }

    return smatch;
}
