set_language (const string &language)
{
#if ENABLE_NLS
#ifndef __BEOS__
    string lang = "LANGUAGE=" + language;
    putenv ((char *) lang.c_str ());
#else

#endif
    {

        extern int _nl_msg_cat_cntr;
        ++_nl_msg_cat_cntr;
    }

    setlocale (LC_MESSAGES, language.c_str ());
#endif
}
