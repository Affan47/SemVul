time_cell_data_function (GtkTreeViewColumn *col,
                                     GtkCellRenderer   *renderer,
                                     GtkTreeModel      *model,
                                     GtkTreeIter       *iter,
                                     gpointer           column)
{
    gdouble    number;
    gchar      buff[TIME_FORMAT_MAX_LENGTH];
    gchar     *fmtstr;
    guint      coli = GPOINTER_TO_UINT (column);
    time_t     t;
    guint size;


    gtk_tree_model_get (model, iter, coli, &number, -1);

    if (number == 0.0) {
        g_object_set (renderer,
                      "text", "--- N/A ---",
                      NULL);
    }
    else {


        t = (number - 2440587.5)*86400.;


        fmtstr = sat_cfg_get_str (SAT_CFG_STR_TIME_FORMAT);


        if (sat_cfg_get_bool (SAT_CFG_BOOL_USE_LOCAL_TIME))
            size = strftime (buff, TIME_FORMAT_MAX_LENGTH, fmtstr, localtime (&t));
        else
            size = strftime (buff, TIME_FORMAT_MAX_LENGTH, fmtstr, gmtime (&t));

        if (size == 0)

            buff[TIME_FORMAT_MAX_LENGTH-1] = '\0';


        g_object_set (renderer,
                      "text", buff,
                      NULL);

        g_free (fmtstr);
    }

}
