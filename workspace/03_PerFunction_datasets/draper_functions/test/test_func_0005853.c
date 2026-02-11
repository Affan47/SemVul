gtk_source_completion_item_finalize (GObject *object)
{
	GtkSourceCompletionItem *self = GTK_SOURCE_COMPLETION_ITEM(object);

	g_free (self->priv->label);
	g_free (self->priv->markup);
	g_free (self->priv->text);

	g_free (self->priv->info);

	if (self->priv->icon != NULL)
	{
		g_object_unref (self->priv->icon);
	}

	G_OBJECT_CLASS (gtk_source_completion_item_parent_class)->finalize (object);
}
