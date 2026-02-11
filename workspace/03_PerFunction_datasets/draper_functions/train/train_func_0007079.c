getpassword_cb(GWEN_GUI *gwen_gui, guint32 flags, const gchar *token,
               const gchar *title, const gchar *text, gchar *buffer,
               gint min_len, gint max_len, guint32 guiid)
{
    GncGWENGui *gui = GETDATA_GUI(gwen_gui);
    gchar *password = NULL;
    gboolean is_tan = (flags & GWEN_GUI_INPUT_FLAGS_TAN) != 0;

    g_return_val_if_fail(gui, -1);

    ENTER("gui=%p, flags=%d, token=%s", gui, flags, token ? token : "(null");


    if (!is_tan && gui->cache_passwords && gui->passwords && token)
    {
        if (flags & GWEN_GUI_INPUT_FLAGS_RETRY)
        {

            g_hash_table_remove(gui->passwords, token);
        }
        else
        {
            gpointer p_var;
            if (g_hash_table_lookup_extended(gui->passwords, token, NULL,
                                             &p_var))
            {

                password = p_var;
                strncpy(buffer, password, max_len);
                buffer[max_len-1] = '\0';

                LEAVE("chose remembered password");
                return 0;
            }
        }
    }

    get_input(gui, flags, title, text, &password, min_len, max_len);

    if (password)
    {

        strncpy(buffer, password, max_len);
        buffer[max_len-1] = '\0';

        if (!is_tan && token)
        {
            if (gui->cache_passwords && gui->passwords)
            {

                DEBUG("Remember password, token=%s", token);
                g_hash_table_insert(gui->passwords, g_strdup(token), password);
            }
            else
            {

                DEBUG("Forget password, token=%s", token);
                erase_password(password);
            }
        }
    }

    LEAVE(" ");
    return password ? 0 : -1;
}
