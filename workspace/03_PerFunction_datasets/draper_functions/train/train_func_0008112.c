exo_wrap_table_forall (GtkContainer *container,
                       gboolean      include_internals,
                       GtkCallback   callback,
                       gpointer      callback_data)
{
  ExoWrapTable *table = EXO_WRAP_TABLE (container);
  GList        *next;
  GList        *node;

  for (node = table->priv->children; node != NULL; node = next)
    {

      g_assert (GTK_IS_WIDGET (node->data));


      next = node->next;


      (*callback) (GTK_WIDGET (node->data), callback_data);
    }
}
