do_passwd(const char * const file,
                     PWInfo * const pwinfo)
{
    if (pwinfo->login == NULL || *(pwinfo->login) == 0) {
        fprintf(stderr, "Missing login\n");
        return PW_ERROR_MISSING_LOGIN;
    }
    if (file == NULL) {
        fprintf(stderr, "Missing passwd file\n");
        return PW_ERROR_MISSING_PASSWD_FILE;
    }
    if ((pwinfo->pwd = do_get_passwd()) == NULL) {
        fprintf(stderr, "Error with entering password - aborting\n");
        return PW_ERROR_ENTER_PASSWD_PW_ERROR;
    }
    do_usermod(file, pwinfo);

    return 0;
}
