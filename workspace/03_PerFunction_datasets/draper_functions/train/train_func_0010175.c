do_preliminary_check(pam_handle_t *handle)
{
        char *filename;
        const char *username;
        int result, fd;

        if (g_mkdir_with_parents (PASSWDDIR, 0) < 0)
                return PAM_AUTHINFO_UNAVAIL;

        result = pam_get_user (handle, &username, "Username: ");
        if (result != PAM_SUCCESS)
                return result;


        filename = g_build_filename (PASSWDDIR, username, NULL);

        fd = open(filename, O_RDWR);
        if (fd < 0 && errno != ENOENT)
                result = PAM_AUTHTOK_ERR;
        else
                result = PAM_SUCCESS;

        g_free(filename);
        if (fd >= 0)
                close(fd);
        return result;
}
