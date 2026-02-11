formatJoystickDescription() {
  char s[256];

  switch(jstate) {
  case 0:
    g_strlcpy(s,_("Move the axis to be used for selecting pieces."),256);
    break;
  case 1:
    g_strlcpy(s,_("Press the button to be used for selecting a square."),256);
    break;
  case 2:
    g_strlcpy(s,_("Move the axis to be used for moving back and forth\nthrough moves of a game."),256);
    break;
  case 3:
    g_strlcpy(s,_("Press the button to be used for going to the previous tab."),256);
    break;
  case 4:
    g_strlcpy(s,_("Press the button to be used for going to the next tab."),256);
    break;
  default:
    snprintf(s,256,_("Board Cursor Axis: %d\nBoard Select Button: %d\nBoard Browsing Axis: %d\nPrevious Tab Button: %d\nNext Tab Button: %d\n"),
	    jsval[0],jsval[1],jsval[2],jsval[3],jsval[4]);
  }
  gtk_label_set_text(GTK_LABEL(jcl), s);
  gtk_widget_queue_resize(jcl);
}
