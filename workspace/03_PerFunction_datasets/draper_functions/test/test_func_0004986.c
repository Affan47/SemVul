find_system_locale()
{
    char *locale_str;
    char *locale_code_pos;

    if(strcmp(options_language, "00")) {
    	strncpy(charlang, options_language, sizeof(charlang));
    	return;
    }

    setlocale(LC_ALL,"");
#ifdef LC_MESSAGES
    locale_str = setlocale(LC_MESSAGES, NULL);
#else
    locale_str = setlocale(LC_ALL, NULL);
#endif

    locale_code_pos = strstr(locale_str, "LC_MESSAGES");
    if (locale_code_pos) {
        locale_code_pos += strlen("LC_MESSAGES") + 1;
    } else {
        locale_code_pos = locale_str;
    }

    if (locale_code_pos[0] && locale_code_pos[1]) {
        snprintf(charlang, sizeof(charlang), "%c%c",
            tolower(locale_code_pos[0]), tolower(locale_code_pos[1]));
    } else {
        strncpy(charlang, "en", sizeof(charlang));
    }

    if ((arch == ARCH_WIN32 || arch == ARCH_WIN64) && !strcmp(charlang, "ge")) {

        strncpy(charlang, "de", sizeof(charlang));
    }
    strncpy(options_language,charlang, sizeof(charlang));
}
