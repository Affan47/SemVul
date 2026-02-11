address_find(void)
{
   int r, found_at;

   r = 0;
   if (glob_find_id) {
      r = clist_find_id(clist,
                        glob_find_id,
                        &found_at);
      if (r) {
         clist_select_row(GTK_CLIST(clist), found_at, ADDRESS_PHONE_COLUMN);
         if (!gtk_clist_row_is_visible(GTK_CLIST(clist), found_at)) {
            gtk_clist_moveto(GTK_CLIST(clist), found_at, 0, 0.5, 0.0);
         }
      }
      glob_find_id = 0;
   }
   return r;
}
