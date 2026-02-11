glade_editable_load (GladeEditable *editable, GladeWidget *widget)
{
  GladeEditableIface *iface;
  g_return_if_fail (GLADE_IS_EDITABLE (editable));
  g_return_if_fail (widget == NULL || GLADE_IS_WIDGET (widget));


  if (!GPOINTER_TO_INT (g_object_get_qdata (G_OBJECT (editable), glade_editable_destroy_quark)))
    {
      g_signal_connect (editable, "destroy", G_CALLBACK (editable_destroyed), NULL);
      g_object_set_qdata (G_OBJECT (editable), glade_editable_destroy_quark, GINT_TO_POINTER (TRUE));
    }

  iface = GLADE_EDITABLE_GET_IFACE (editable);

  g_object_set_qdata (G_OBJECT (editable), glade_editable_loading_quark, GINT_TO_POINTER (TRUE));

  if (iface->load)
    iface->load (editable, widget);
  else
    g_critical ("No GladeEditable::load() support on type %s",
                G_OBJECT_TYPE_NAME (editable));

  g_object_set_qdata (G_OBJECT (editable), glade_editable_loading_quark, GINT_TO_POINTER (FALSE));
}
