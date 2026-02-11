_forsPAFHeaderCreate(const char *name, const char *type, const char *id,
                    const char *desc, int *pos)
{

    ForsPAFRecord **hdr;
    const char *user, *timestamp;
#if defined HAVE_GETUID && defined HAVE_GETPWUID
    struct passwd *pw;
#endif


#if defined HAVE_GETUID && defined HAVE_GETPWUID
    pw = getpwuid(getuid());

    if (!pw)
        return NULL;

    user = pw->pw_name;
#else
    user = getenv("USER");
    user = user == NULL ? getenv("LOGNAME") : user;

    if (!user)
    {
        return NULL;
    }
#endif


    timestamp = getTimeISO8601();

    pos[0] = 0;

    _forsPAFAppend(&hdr, pos, PAF_HDR_START, PAF_TYPE_NONE, NULL, NULL);
    _forsPAFAppend(&hdr, pos, PAF_TYPE, PAF_TYPE_STRING, type,
                  "Type of parameter file");

    if (id) {
        _forsPAFAppend(&hdr, pos, PAF_ID, PAF_TYPE_STRING, id, NULL);
    }
    else {
        _forsPAFAppend(&hdr, pos, PAF_ID, PAF_TYPE_STRING, "", NULL);
    }

    _forsPAFAppend(&hdr, pos, PAF_NAME, PAF_TYPE_STRING, name, "Name of PAF");

    if (desc)
        _forsPAFAppend(&hdr, pos, PAF_DESC, PAF_TYPE_STRING, desc,
                      "Short description of PAF");
    else
        _forsPAFAppend(&hdr, pos, PAF_DESC, PAF_TYPE_STRING, "",
                      "Short description of PAF");

    _forsPAFAppend(&hdr, pos, PAF_CRTE_NAME, PAF_TYPE_STRING, user,
                  "Name of creator");
    _forsPAFAppend(&hdr, pos, PAF_CRTE_TIME, PAF_TYPE_STRING, timestamp,
                  "Civil time for creation");
    _forsPAFAppend(&hdr, pos, PAF_LCHG_NAME, PAF_TYPE_STRING, user,
                  "Author of par. file");
    _forsPAFAppend(&hdr, pos, PAF_LCHG_TIME, PAF_TYPE_STRING, timestamp,
                  "Timestamp for last change");
    _forsPAFAppend(&hdr, pos, PAF_CHCK_NAME, PAF_TYPE_STRING, "",
                  "Name of appl. checking");
    _forsPAFAppend(&hdr, pos, PAF_CHCK_TIME, PAF_TYPE_STRING, "",
                  "Time for checking");
    _forsPAFAppend(&hdr, pos, PAF_CHCK_CHECKSUM, PAF_TYPE_STRING, "",
                  "Checksum for the PAF");
    _forsPAFAppend(&hdr, pos, PAF_HDR_END, PAF_TYPE_NONE, NULL, NULL);

    return hdr;

}
