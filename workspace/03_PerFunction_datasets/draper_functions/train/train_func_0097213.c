x_dialog_delattrib()
{
  GtkWidget *dialog;
  gint mincol, maxcol;
  GtkSheet *sheet;
  gint cur_page;


  cur_page = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
  sheet = GTK_SHEET(sheets[cur_page]);
  if (sheet == NULL) {
    return;
  }

  mincol = x_gtksheet_get_min_col(sheet);
  maxcol =  x_gtksheet_get_max_col(sheet);

  if ( (mincol != maxcol) || (mincol == -1) || (maxcol == -1) ) {

    return;
  }


  dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_QUESTION,
                                  GTK_BUTTONS_YES_NO,
                                  "Are you sure you want to delete this attribute?");

  gtk_window_set_title(GTK_WINDOW(dialog), "Delete attribute");
  switch(gtk_dialog_run(GTK_DIALOG(dialog))) {
    case GTK_RESPONSE_YES:

      s_toplevel_delete_attrib_col();

      break;

    default:
      break;
  }

  gtk_widget_destroy(dialog);
}
