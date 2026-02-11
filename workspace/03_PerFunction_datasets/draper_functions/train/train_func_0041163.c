datebook_gui_setdate(int year, int month, int day)
{

   current_year = year;
   current_month = month;
   current_day = day;


   datebook_refresh(FALSE, FALSE);


   if (window) {
      gtk_window_present(GTK_WINDOW(window));
   }
}
