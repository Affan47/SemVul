glade_editor_load_editable (GladeEditor *editor,
                            GladeWidget *widget,
                            GladeEditorPageType type)
{
  GtkWidget   *editable;
  GladeWidget *parent = glade_widget_get_parent (widget);


  if (type == GLADE_PAGE_PACKING)
    {
      GladeWidgetAdaptor *adaptor;

      if (!parent)
	return;

      adaptor = glade_widget_get_adaptor (parent);
      editable =
	glade_editor_load_editable_in_page (editor, adaptor,
					    GLADE_PAGE_PACKING);
    }
  else
    editable =
      glade_editor_get_editable_by_adaptor (editor,
					    glade_widget_get_adaptor (widget),
					    type);

  g_assert (editable);

  if (!widget)
    gtk_widget_hide (editable);

  glade_editable_load (GLADE_EDITABLE (editable), widget);

  if (widget)
    gtk_widget_show (editable);
}
