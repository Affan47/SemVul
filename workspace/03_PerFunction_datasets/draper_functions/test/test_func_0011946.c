create_colorselectiondialog1 (void)
{
  GtkWidget *colorselectiondialog1;
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;
  GtkWidget *help_button1;
  GtkWidget *color_selection1;

  colorselectiondialog1 = gtk_color_selection_dialog_new (_("Select Color"));
  gtk_widget_set_name (colorselectiondialog1, "colorselectiondialog1");
  gtk_container_set_border_width (GTK_CONTAINER (colorselectiondialog1), 5);
  gtk_window_set_resizable (GTK_WINDOW (colorselectiondialog1), FALSE);
  gtk_window_set_type_hint (GTK_WINDOW (colorselectiondialog1), GDK_WINDOW_TYPE_HINT_DIALOG);

  ok_button1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog1)->ok_button;
  gtk_widget_set_name (ok_button1, "ok_button1");
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  cancel_button1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog1)->cancel_button;
  gtk_widget_set_name (cancel_button1, "cancel_button1");
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  help_button1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog1)->help_button;
  gtk_widget_set_name (help_button1, "help_button1");
  gtk_widget_show (help_button1);
  GTK_WIDGET_SET_FLAGS (help_button1, GTK_CAN_DEFAULT);

  color_selection1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog1)->colorsel;
  gtk_widget_set_name (color_selection1, "color_selection1");
  gtk_widget_show (color_selection1);
  gtk_container_set_border_width (GTK_CONTAINER (color_selection1), 5);
  gtk_color_selection_set_has_opacity_control (GTK_COLOR_SELECTION (color_selection1), FALSE);


  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog1, colorselectiondialog1, "colorselectiondialog1");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog1, ok_button1, "ok_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog1, cancel_button1, "cancel_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog1, help_button1, "help_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog1, color_selection1, "color_selection1");

  return colorselectiondialog1;
}
