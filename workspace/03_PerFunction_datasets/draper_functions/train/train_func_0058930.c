var_dlmodEntry(struct variable * vp,
               oid * name,
               size_t * length,
               int exact, size_t * var_len, WriteMethod ** write_method)
{


    struct dlmod   *dlm;

    *var_len = sizeof(int);


    dlm =
        header_dlmodEntry(vp, name, length, exact, var_len, write_method);
    if (dlm == NULL)
        return NULL;


    switch (vp->magic) {
    case DLMODNAME:
        *write_method = write_dlmodName;
        *var_len = strlen(dlm->name);
        return (unsigned char *) dlm->name;
    case DLMODPATH:
        *write_method = write_dlmodPath;
        *var_len = strlen(dlm->path);
        return (unsigned char *) dlm->path;
    case DLMODERROR:
        *var_len = strlen(dlm->error);
        return (unsigned char *) dlm->error;
    case DLMODSTATUS:
        *write_method = write_dlmodStatus;
        long_return = dlm->status;
        return (unsigned char *) &long_return;
    default:
        DEBUGMSGTL(("dlmod", "unknown sub-id %d in var_dlmodEntry\n",
                    vp->magic));
    }
    return NULL;
}
