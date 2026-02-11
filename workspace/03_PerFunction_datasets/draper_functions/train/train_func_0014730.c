fm_archiver_is_mime_type_supported(FmArchiver* archiver, const char* type)
{
    char** p;
    if(G_UNLIKELY(!type))
        return FALSE;
    for(p=archiver->mime_types; *p; ++p)
    {
        if(strcmp(*p, type) == 0)
            return TRUE;
    }
    return FALSE;
}
