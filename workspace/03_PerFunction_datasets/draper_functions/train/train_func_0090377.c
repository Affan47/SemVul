get_locale_encoding(void)
{
#ifdef MS_WINDOWS
    char codepage[100];
    PyOS_snprintf(codepage, sizeof(codepage), "cp%d", GetACP());
    return get_codec_name(codepage);
#elif defined(HAVE_LANGINFO_H) && defined(CODESET)
    char* codeset = nl_langinfo(CODESET);
    if (!codeset || codeset[0] == '\0') {
        PyErr_SetString(PyExc_ValueError, "CODESET is not set or empty");
        return NULL;
    }
    return get_codec_name(codeset);
#else
    PyErr_SetNone(PyExc_NotImplementedError);
    return NULL;
#endif
}
