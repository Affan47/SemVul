select_age (void)
{
     gint num = sat_cfg_get_int (SAT_CFG_INT_LOG_CLEAN_AGE);

     switch (num) {

     case SEC_PER_DAY:
          gtk_combo_box_set_active (GTK_COMBO_BOX (age), 1);
          break;

     case SEC_PER_WEEK:
          gtk_combo_box_set_active (GTK_COMBO_BOX (age), 2);
          break;

     case SEC_PER_MONTH:
          gtk_combo_box_set_active (GTK_COMBO_BOX (age), 3);
          break;

     default:
          gtk_combo_box_set_active (GTK_COMBO_BOX (age), 0);
     }

}
