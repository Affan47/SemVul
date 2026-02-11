reset_cb               (GtkWidget *button, gpointer cfg)
{
     guint32 flags;
     guint i;


     if (cfg == NULL) {

          flags = sat_cfg_get_int_def (SAT_CFG_INT_LIST_COLUMNS);
          gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (ruleshint),
                                               sat_cfg_get_bool_def (SAT_CFG_BOOL_RULES_HINT));
     }
     else {

          flags = sat_cfg_get_int (SAT_CFG_INT_LIST_COLUMNS);
     }


     for (i = 0; i < SAT_LIST_COL_NUMBER; i++) {

          gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check[i]),
                                               flags & (1 << i));

     }


     dirty = FALSE;
     reset = TRUE;

}
