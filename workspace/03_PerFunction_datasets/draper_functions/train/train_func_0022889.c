cb_hide_menu_time(GtkWidget *widget, gpointer data)
{


   if (datebook_version == 0) {
      if (begin_date.tm_hour > end_date.tm_hour)
      {
         end_date.tm_hour = begin_date.tm_hour;
      }
   }

   set_begin_end_labels(&begin_date, &end_date, UPDATE_DATE_MENUS |
                                                UPDATE_DATE_ENTRIES);

   return FALSE;
}
