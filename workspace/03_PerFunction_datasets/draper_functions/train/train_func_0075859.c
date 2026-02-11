Jim_PackageProvide(Jim_Interp *interp, const char *name, const char *ver, int flags)
{

    Jim_HashEntry *he = Jim_FindHashEntry(&interp->packages, name);


    if (he && *(const char *)he->u.val) {
        if (flags & JIM_ERRMSG) {
            Jim_SetResultFormatted(interp, "package \"%s\" was already provided", name);
        }
        return JIM_ERR;
    }
    if (he) {
        Jim_DeleteHashEntry(&interp->packages, name);
    }
    Jim_AddHashEntry(&interp->packages, name, (char *)ver);
    return JIM_OK;
}
