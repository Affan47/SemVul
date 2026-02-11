mouse_button_callback( GtkWidget *widget,GdkEventButton *event, gpointer data)
{

  switch (event->button) {
    case 1:
      toggle_win_sym();
      break;
    case 2:
      inmd_switch_popup_handler(widget, (GdkEvent *)event);
      break;
    case 3:
      exec_gcin_setup();
      break;
  }

}
