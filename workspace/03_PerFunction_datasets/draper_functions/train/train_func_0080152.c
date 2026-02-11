create_loc_selector   (GKeyFile *cfgdata)
{
    GtkWidget    *combo;
    GDir         *dir = NULL;
    GError       *error = NULL;
    gchar        *dirname;
    const gchar  *filename;
    gchar        *defqth = NULL;
    gchar        *defqthshort = NULL;
    gchar       **buffv;
    gint         idx = -1;
    gint         count = 0;
    GSList      *qths=NULL;
    gchar       *qthname;
    gint         i,n;

    combo = gtk_combo_box_new_text ();


    if (g_key_file_has_key (cfgdata, MOD_CFG_GLOBAL_SECTION, MOD_CFG_QTH_FILE_KEY, NULL)) {
        defqth = g_key_file_get_string (cfgdata,
                                        MOD_CFG_GLOBAL_SECTION,
                                        MOD_CFG_QTH_FILE_KEY,
                                        &error);
        buffv = g_strsplit (defqth, ".qth", 0);
        defqthshort = g_strdup(buffv[0]);

        g_strfreev(buffv);
    }
    else {
        sat_log_log (SAT_LOG_LEVEL_MSG,
                     _("%s: Module has no QTH; use default."),
                     __FUNCTION__);

        defqth = g_strdup (_("** DEFAULT **"));
        defqthshort = g_strdup(defqth);
    }


    dirname = get_user_conf_dir ();
    dir = g_dir_open (dirname, 0, &error);

    if (dir) {
        while ((filename = g_dir_read_name (dir))) {

            if (g_str_has_suffix (filename, ".qth")) {

                buffv = g_strsplit (filename, ".qth", 0);
                qths = g_slist_insert_sorted(qths,g_strdup(buffv[0]),(GCompareFunc) qth_name_compare);
                g_strfreev (buffv);

            }

        }
        n = g_slist_length (qths);
        for (i = 0; i < n; i++) {
            qthname = g_slist_nth_data (qths, i);
            if (qthname) {
                gtk_combo_box_append_text (GTK_COMBO_BOX (combo), qthname);


                if (!g_ascii_strcasecmp (defqthshort, qthname)) {
                    idx = count;
                }
                g_free(qthname);
                count++;
            }
        }
        g_slist_free(qths);

    }
    else {
        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s:%d: Failed to open user cfg dir %s (%s)"),
                     __FILE__, __LINE__, dirname, error->message);
        g_clear_error (&error);
    }


    gtk_combo_box_append_text (GTK_COMBO_BOX (combo), _("** DEFAULT **"));


    if (idx == -1) {
        gtk_combo_box_set_active (GTK_COMBO_BOX (combo), count);
    }
    else {
        gtk_combo_box_set_active (GTK_COMBO_BOX (combo), idx);
    }

    g_free (defqth);
    g_free (defqthshort);
    g_free (dirname);
    g_dir_close (dir);


    return combo;
}
