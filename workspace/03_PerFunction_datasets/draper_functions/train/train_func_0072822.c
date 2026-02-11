sat_pref_help_ok     ()
{
     gint idx;

     if (dirty) {

          idx = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));
          sat_cfg_set_int (SAT_CFG_INT_WEB_BROWSER_TYPE, idx);


          if (idx == BROWSER_TYPE_OTHER) {
               sat_cfg_set_str (SAT_CFG_STR_WEB_BROWSER,
                          gtk_entry_get_text (GTK_ENTRY (entry)));
          }
          else {
               sat_cfg_reset_str (SAT_CFG_STR_WEB_BROWSER);
          }

     }
     dirty = FALSE;
}
