DXUnloadObjFile(char *fname, char *envvar)
{
    char *foundname = NULL;
    struct loadtable *lp = NULL;

    if (!findfile(fname, &foundname, envvar))
	return ERROR;

    if (((lp = get_tp_entry(foundname)) != NULL) &&
	(lp->loadstate == L_UNLOADED)) {
	DXDebug("L", "`%s' found but already unloaded", foundname);
	DXFree((Pointer)foundname);
	return OK;
    }

    if (!lp) {
	DXDebug("L", "`%s' not found in load list", foundname);
	DXSetError(ERROR_BAD_PARAMETER,
		   "cannot unload `%s'; not found in load list", foundname);
	DXFree((Pointer)foundname);
	return OK;
    }

    if (dlclose(lp->h) < 0) {
	DXSetError(ERROR_DATA_INVALID, "cannot unload file '%s', %s",
		   foundname, strerror(errno));
	DXFree((Pointer)foundname);
	return ERROR;
    }

    if (!set_tp_entry(L_UNLOADED, foundname, (Handle)0, (EntryPt)0)) {
	DXFree((Pointer)foundname);
	return ERROR;
    }

    DXFree((Pointer)foundname);
    return OK;
}
