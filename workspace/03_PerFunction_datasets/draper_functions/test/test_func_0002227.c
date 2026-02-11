gretl_bundle_set_creator (gretl_bundle *bundle, const char *name)
{
    int err = 0;

    if (bundle == NULL) {
	err = E_DATA;
    } else {
	free(bundle->creator);
	if (name == NULL) {
	    bundle->creator = NULL;
	} else {
	    bundle->creator = gretl_strdup(name);
	    if (bundle->creator == NULL) {
		err = E_ALLOC;
	    }
	}
    }

    return err;
}
