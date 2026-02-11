autonumber_text_response(GtkWidget * widget, gint response,
			      AUTONUMBER_TEXT *autotext)
{
  switch (response) {
  case GTK_RESPONSE_ACCEPT:
    autonumber_get_state(autotext);
    if (autotext->removenum == TRUE && autotext->scope_overwrite == FALSE) {

      autotext->scope_overwrite = TRUE;
      autonumber_text_autonumber(autotext);
      autotext->scope_overwrite = FALSE;
    }
    else {
      autonumber_text_autonumber(autotext);
    }
    break;
  case GTK_RESPONSE_REJECT:
  case GTK_RESPONSE_DELETE_EVENT:
    gtk_widget_destroy(autotext->dialog);
    autotext->dialog = NULL;
    break;
  default:
    printf("ERROR: autonumber_text_response(): strange signal %d\n",response);
  }
}
