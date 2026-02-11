test_types (void)
{
  const gchar buffer[] =
    "<interface>"
    "  <object class=\"GtkAction\" id=\"action\"/>"
    "  <object class=\"GtkActionGroup\" id=\"actiongroup\"/>"
    "  <object class=\"GtkAlignment\" id=\"alignment\"/>"
    "  <object class=\"GtkArrow\" id=\"arrow\"/>"
    "  <object class=\"GtkButton\" id=\"button\"/>"
    "  <object class=\"GtkCheckButton\" id=\"checkbutton\"/>"
    "  <object class=\"GtkDialog\" id=\"dialog\"/>"
    "  <object class=\"GtkDrawingArea\" id=\"drawingarea\"/>"
    "  <object class=\"GtkEventBox\" id=\"eventbox\"/>"
    "  <object class=\"GtkEntry\" id=\"entry\"/>"
    "  <object class=\"GtkFontButton\" id=\"fontbutton\"/>"
    "  <object class=\"GtkHButtonBox\" id=\"hbuttonbox\"/>"
    "  <object class=\"GtkHBox\" id=\"hbox\"/>"
    "  <object class=\"GtkHPaned\" id=\"hpaned\"/>"
    "  <object class=\"GtkHRuler\" id=\"hruler\"/>"
    "  <object class=\"GtkHScale\" id=\"hscale\"/>"
    "  <object class=\"GtkHScrollbar\" id=\"hscrollbar\"/>"
    "  <object class=\"GtkHSeparator\" id=\"hseparator\"/>"
    "  <object class=\"GtkImage\" id=\"image\"/>"
    "  <object class=\"GtkLabel\" id=\"label\"/>"
    "  <object class=\"GtkListStore\" id=\"liststore\"/>"
    "  <object class=\"GtkMenuBar\" id=\"menubar\"/>"
    "  <object class=\"GtkNotebook\" id=\"notebook\"/>"
    "  <object class=\"GtkProgressBar\" id=\"progressbar\"/>"
    "  <object class=\"GtkRadioButton\" id=\"radiobutton\"/>"
    "  <object class=\"GtkSizeGroup\" id=\"sizegroup\"/>"
    "  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow\"/>"
    "  <object class=\"GtkSpinButton\" id=\"spinbutton\"/>"
    "  <object class=\"GtkStatusbar\" id=\"statusbar\"/>"
    "  <object class=\"GtkTextView\" id=\"textview\"/>"
    "  <object class=\"GtkToggleAction\" id=\"toggleaction\"/>"
    "  <object class=\"GtkToggleButton\" id=\"togglebutton\"/>"
    "  <object class=\"GtkToolbar\" id=\"toolbar\"/>"
    "  <object class=\"GtkTreeStore\" id=\"treestore\"/>"
    "  <object class=\"GtkTreeView\" id=\"treeview\"/>"
    "  <object class=\"GtkTable\" id=\"table\"/>"
    "  <object class=\"GtkVBox\" id=\"vbox\"/>"
    "  <object class=\"GtkVButtonBox\" id=\"vbuttonbox\"/>"
    "  <object class=\"GtkVScrollbar\" id=\"vscrollbar\"/>"
    "  <object class=\"GtkVSeparator\" id=\"vseparator\"/>"
    "  <object class=\"GtkViewport\" id=\"viewport\"/>"
    "  <object class=\"GtkVRuler\" id=\"vruler\"/>"
    "  <object class=\"GtkVPaned\" id=\"vpaned\"/>"
    "  <object class=\"GtkVScale\" id=\"vscale\"/>"
    "  <object class=\"GtkWindow\" id=\"window\"/>"
    "  <object class=\"GtkUIManager\" id=\"uimanager\"/>"
    "</interface>";
  const gchar buffer2[] =
    "<interface>"
    "  <object type-func=\"gtk_window_get_type\" id=\"window\"/>"
    "</interface>";
  const gchar buffer3[] =
    "<interface>"
    "  <object type-func=\"xxx_invalid_get_type_function\" id=\"window\"/>"
    "</interface>";
  GObject *window;
  GError *error;

  builder = builder_new_from_string (buffer, -1, NULL);
  gtk_widget_destroy (GTK_WIDGET (gtk_builder_get_object (builder, "dialog")));
  gtk_widget_destroy (GTK_WIDGET (gtk_builder_get_object (builder, "window")));
  g_object_unref (builder);

  builder = builder_new_from_string (buffer2, -1, NULL);
  window = gtk_builder_get_object (builder, "window");
  cut_assert (window != NULL);
  cut_assert (GTK_IS_WINDOW (window));
  gtk_widget_destroy (GTK_WIDGET (window));
  g_object_unref (builder);

  error = NULL;
  builder = gtk_builder_new ();
  gtk_builder_add_from_string (builder, buffer3, -1, &error);
  cut_assert (error != NULL);
  cut_assert (error->domain == GTK_BUILDER_ERROR);
  cut_assert (error->code == GTK_BUILDER_ERROR_INVALID_TYPE_FUNCTION);
  g_error_free (error);
  g_object_unref (builder);

  builder = NULL;
}
