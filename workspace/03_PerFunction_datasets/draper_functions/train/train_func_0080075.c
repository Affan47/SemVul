cal_popup_key_pressed (EggDateTime *edt, GdkEventKey *event, GtkWidget *widget)
{
   if (event->keyval != GDK_Escape)
      return FALSE;

   g_signal_stop_emission_by_name (G_OBJECT (widget), "key_press_event");

   cal_popup_hide (edt);

   return TRUE;
}
