pam_sm_authenticate (pam_handle_t  *handle,
		     int            flags,
		     int            argc,
		     const char   **argv)
{
        const char *username;
        char *filename = NULL;
        char *ciphertext = NULL;
        size_t ciphertext_len;
        const char *pin;
        char *password;
        int result;
        GError *error;

        init_libgcrypt ();


        if (g_mkdir_with_parents (PASSWDDIR, 0) < 0)
                return PAM_AUTHINFO_UNAVAIL;


        result = pam_get_user (handle, &username, "Username: ");
        if (result != PAM_SUCCESS)
                return result;

        filename = g_build_filename (PASSWDDIR, username, NULL);

        error = NULL;
        if (!g_file_get_contents (filename, &ciphertext, &ciphertext_len, &error)) {
                if (g_error_matches (error, G_FILE_ERROR, G_FILE_ERROR_NOENT))
                        result = PAM_AUTHINFO_UNAVAIL;
                else
                        result = PAM_AUTHTOK_ERR;

                g_error_free (error);
                goto out;
        }


        result = pam_get_authtok (handle, PAM_AUTHTOK, &pin, "PIN");
        if (result != PAM_SUCCESS)
                goto out;

        password = decode_password (ciphertext, ciphertext_len, pin);
        if (password)
                result = pam_set_item (handle, PAM_AUTHTOK, password);
        else
                result = PAM_AUTH_ERR;

 out:
        g_free (ciphertext);
        g_free (filename);

        return result;
}
