mytunetsvc_get_user_config(USERCONFIG *uc)
{
    STRING *str = NULL;
    CHAR username[200], password[200];
    CHAR *szConfigFile = mytunetsvc_config_file();

    memset(uc, 0, sizeof(USERCONFIG));

    str = setting_read(szConfigFile, "username", "");
    if(strlen(str->str) >= sizeof(username))
        strcpy(username, "");
    else
        strcpy(username, str->str);
    str = string_free(str);


    str = setting_read(szConfigFile, "password", "");
    DecodePasswordByUsername(username, str->str, password);
    str = string_free(str);


    userconfig_set_username(uc, username);
    userconfig_set_password_by_md5(uc, password);


    str = setting_read(szConfigFile, "adapter", "");
    userconfig_set_adapter(uc, str->str);
    str = string_free(str);

    userconfig_set_language(uc, setting_read_int(szConfigFile, "language", mytunet_default_language));
    userconfig_set_limitation(uc, setting_read_int(szConfigFile, "limitation", 0));

    userconfig_set_dot1x(uc, setting_read_int(szConfigFile, "usedot1x", 1), 0);

    return OK;
}
