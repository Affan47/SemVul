expense_find(int unique_id)
{
   int r, found_at;

   jp_logf(JP_LOG_DEBUG, "Expense: expense_find, unique_id=%d\n",unique_id);

   if (unique_id)
   {
      r = expense_clist_find_id(clist,
                        unique_id,
                        &found_at);
      if (r) {
         gtk_clist_select_row(GTK_CLIST(clist), found_at, 0);
         if (!gtk_clist_row_is_visible(GTK_CLIST(clist), found_at)) {
            gtk_clist_moveto(GTK_CLIST(clist), found_at, 0, 0.5, 0.0);
         }
      }
   }

   return EXIT_SUCCESS;
}
