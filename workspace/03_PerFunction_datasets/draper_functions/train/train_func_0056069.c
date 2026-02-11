get_session_keyfile_if_valid (const char *path)
{
        GKeyFile  *keyfile;
        gsize      len;
        char     **list;

        g_debug ("fill: *** Looking if %s is a valid session file", path);

        keyfile = g_key_file_new ();

        if (!g_key_file_load_from_file (keyfile, path, G_KEY_FILE_NONE, NULL)) {
                g_debug ("Cannot use session '%s': non-existing or invalid file.", path);
                goto error;
        }

        if (!g_key_file_has_group (keyfile, GSM_KEYFILE_SESSION_GROUP)) {
                g_warning ("Cannot use session '%s': no '%s' group.", path, GSM_KEYFILE_SESSION_GROUP);
                goto error;
        }


        if (len == 0) {
                list = g_key_file_get_string_list (keyfile,
                                                   GSM_KEYFILE_SESSION_GROUP,
                                                   GSM_KEYFILE_REQUIRED_COMPONENTS_KEY,
                                                   &len, NULL);
                if (list)
                        g_strfreev (list);
                if (len == 0)
                        g_warning ("Session '%s': no component in the session.", path);
        }

        return keyfile;

error:
        g_key_file_free (keyfile);
        return NULL;
}
