cmsOpenProfileFromStreamTHR(cmsContext ContextID, FILE* ICCProfile, const char *sAccess)
{
    _cmsICCPROFILE* NewIcc;
    cmsHPROFILE hEmpty = cmsCreateProfilePlaceholder(ContextID);

    if (hEmpty == NULL) return NULL;

    NewIcc = (_cmsICCPROFILE*) hEmpty;

    NewIcc ->IOhandler = cmsOpenIOhandlerFromStream(ContextID, ICCProfile);
    if (NewIcc ->IOhandler == NULL) goto Error;

    if (*sAccess == 'w') {

        NewIcc -> IsWrite = TRUE;
        return hEmpty;
    }

    if (!_cmsReadHeader(NewIcc)) goto Error;
    return hEmpty;

Error:
    cmsCloseProfile(hEmpty);
    return NULL;

}
