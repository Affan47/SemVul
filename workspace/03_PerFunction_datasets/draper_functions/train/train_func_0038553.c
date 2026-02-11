glade_gtk_switch_create_editable (GladeWidgetAdaptor *adaptor,
                                  GladeEditorPageType type)
{
  if (type == GLADE_PAGE_GENERAL)
    return (GladeEditable *) glade_activatable_editor_new (adaptor, NULL);

  return GWA_GET_CLASS (GTK_TYPE_WIDGET)->create_editable (adaptor, type);
}
