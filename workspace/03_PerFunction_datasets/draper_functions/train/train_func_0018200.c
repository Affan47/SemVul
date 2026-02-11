profile_ser_internalize(const char *unused, profile_t *profilep,
                                  unsigned char **bufpp, size_t *remainp)
{
    errcode_t               retval;
    unsigned char   *bp;
    size_t          remain;
    int                     i;
    prof_int32              fcount, tmp;
    profile_filespec_t              *flist = 0;

    bp = *bufpp;
    remain = *remainp;
    fcount = 0;

    if (remain >= 12)
        (void) unpack_int32(&tmp, &bp, &remain);
    else
        tmp = 0;

    if (tmp != PROF_MAGIC_PROFILE) {
        retval = EINVAL;
        goto cleanup;
    }

    (void) unpack_int32(&fcount, &bp, &remain);
    retval = ENOMEM;

    flist = (profile_filespec_t *) malloc(sizeof(profile_filespec_t) * (size_t) (fcount + 1));
    if (!flist)
        goto cleanup;

    memset(flist, 0, sizeof(char *) * (size_t) (fcount+1));
    for (i=0; i<fcount; i++) {
        if (!unpack_int32(&tmp, &bp, &remain)) {
            flist[i] = (char *) malloc((size_t) (tmp+1));
            if (!flist[i])
                goto cleanup;
            memcpy(flist[i], bp, (size_t) tmp);
            flist[i][tmp] = '\0';
            bp += tmp;
            remain -= (size_t) tmp;
        }
    }

    if (unpack_int32(&tmp, &bp, &remain) ||
        (tmp != PROF_MAGIC_PROFILE)) {
        retval = EINVAL;
        goto cleanup;
    }

    if ((retval = profile_init((const_profile_filespec_t *) flist,
                               profilep)))
        goto cleanup;

    *bufpp = bp;
    *remainp = remain;

cleanup:
    if (flist) {
        for (i=0; i<fcount; i++) {
            if (flist[i])
                free(flist[i]);
        }
        free(flist);
    }
    return(retval);
}
