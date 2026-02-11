create_and_fill_models (GtkSatSelector *selector)
{
    GtkListStore *store;
    GtkTreeIter   node;
    GDir         *dir;
    gchar        *dirname;
    sat_t         sat;
    gint          catnum;

    gchar       **buffv;
    const gchar  *fname;
    gchar        *nfname;

    guint         num = 0;
    gint          i,n;
    GSList       *cats = NULL;


    store = gtk_list_store_new (GTK_SAT_SELECTOR_COL_NUM,
                                G_TYPE_STRING,
                                G_TYPE_INT,
                                G_TYPE_DOUBLE,
                                G_TYPE_BOOLEAN
                                );
    selector->models = g_slist_append (selector->models, store);
    gtk_combo_box_append_text (GTK_COMBO_BOX (selector->groups), _("All satellites"));
    gtk_combo_box_set_active (GTK_COMBO_BOX (selector->groups), 0);

    dirname = get_satdata_dir ();
    dir = g_dir_open (dirname, 0, NULL);
    if (!dir) {
        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s:%s: Failed to open satdata directory %s."),
                     __FILE__, __FUNCTION__, dirname);

        g_free (dirname);

        return;
    }


    while ((fname = g_dir_read_name (dir))) {

        if (g_str_has_suffix (fname, ".sat")) {

            buffv = g_strsplit (fname, ".", 0);
            catnum = (gint) g_ascii_strtoll (buffv[0], NULL, 0);

            if (gtk_sat_data_read_sat (catnum, &sat)) {

            }
            else {


                gtk_list_store_append (store, &node);
                gtk_list_store_set (store, &node,
                                    GTK_SAT_SELECTOR_COL_NAME, sat.nickname,
                                    GTK_SAT_SELECTOR_COL_CATNUM, catnum,
                                    GTK_SAT_SELECTOR_COL_EPOCH, sat.jul_epoch,
                                    GTK_SAT_SELECTOR_COL_SELECTED, FALSE,
                                    -1);

                g_free (sat.name);
                g_free (sat.nickname);
                num++;
            }

            g_strfreev (buffv);
        }
    }
    sat_log_log (SAT_LOG_LEVEL_MSG,
                 _("%s:%s: Read %d satellites into MAIN group."),
                 __FILE__, __FUNCTION__, num);


    g_dir_rewind (dir);
    while ((fname = g_dir_read_name (dir))) {
        if (g_str_has_suffix (fname, ".cat")) {
            cats = g_slist_insert_sorted(cats,g_strdup(fname),(GCompareFunc)cat_file_compare);
        }
    }


    n = g_slist_length (cats);
    for (i = 0; i < n; i++) {
        nfname = g_slist_nth_data (cats, i);
        if (nfname) {
            load_cat_file (selector, nfname);
        }
        g_free(nfname);
    }
    g_slist_free (cats);

    g_dir_close (dir);
    g_free (dirname);

}
