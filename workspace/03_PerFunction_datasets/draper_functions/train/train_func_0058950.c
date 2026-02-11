select_location       (GtkWidget *widget, gpointer data)
{
    guint    mode = GPOINTER_TO_UINT (data);
    guint    flags;
    gchar   *qthloc;
    gchar   *qthwx;
    gfloat   qthlat;
    gfloat   qthlon;
    guint    qthalt;
    gboolean selected = FALSE;


    switch (mode) {


    case SELECTION_MODE_WX:
        flags = TREE_COL_FLAG_NAME | TREE_COL_FLAG_WX;
        break;

    default:
        flags = TREE_COL_FLAG_NAME |
                TREE_COL_FLAG_LAT  |
                TREE_COL_FLAG_LON  |
                TREE_COL_FLAG_ALT  |
                TREE_COL_FLAG_WX;

        mode = SELECTION_MODE_LOC;
        break;
    }

    selected = loc_tree_create (NULL, flags, &qthloc, &qthlat, &qthlon, &qthalt, &qthwx);

    if (selected) {

        switch (mode) {

                case SELECTION_MODE_WX:
            gtk_entry_set_text (GTK_ENTRY (wx), qthwx);
            break;

                case SELECTION_MODE_LOC:
            gtk_entry_set_text (GTK_ENTRY (location), qthloc);
            gtk_entry_set_text (GTK_ENTRY (wx), qthwx);

            gtk_spin_button_set_value (GTK_SPIN_BUTTON (lat), fabs (qthlat));
            if (qthlat < 0.00)
                gtk_combo_box_set_active (GTK_COMBO_BOX (ns), 1);
            else
                gtk_combo_box_set_active (GTK_COMBO_BOX (ns), 0);

            gtk_spin_button_set_value (GTK_SPIN_BUTTON (lon), fabs (qthlon));
            if (qthlon < 0.00)
                gtk_combo_box_set_active (GTK_COMBO_BOX (ew), 1);
            else
                gtk_combo_box_set_active (GTK_COMBO_BOX (ew), 0);

            gtk_spin_button_set_value (GTK_SPIN_BUTTON (alt), qthalt);

            break;

                default:

            break;
        }


        g_free (qthloc);
        g_free (qthwx);
    }


}
