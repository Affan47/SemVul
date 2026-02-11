gui_dialog_present(struct gui_dialog *dlg)
{
  fc_assert_ret(NULL != dlg);

  switch (dlg->type) {
  case GUI_DIALOG_WINDOW:
    gtk_widget_show(dlg->v.window);
    break;
  case GUI_DIALOG_TAB:
    {
      GtkNotebook *notebook = GTK_NOTEBOOK(dlg->v.tab.notebook);
      gint current, n;

      current = gtk_notebook_get_current_page(notebook);
      n = gtk_notebook_page_num(notebook, dlg->vbox);

      if (current != n) {
	GtkWidget *label = dlg->v.tab.label;
	GdkRGBA color = {.red = 1.0, .green = 0, .blue = 0, .alpha = 1.0};

	gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color);
      }
    }
    break;
  }
}
