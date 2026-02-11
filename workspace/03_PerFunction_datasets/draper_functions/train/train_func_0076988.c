impl_dispose (GObject *object)
{
	RBObjectPropertyEditor *editor = RB_OBJECT_PROPERTY_EDITOR (object);

	if (editor->priv->object != NULL) {
		if (editor->priv->notify_id) {
			g_signal_handler_disconnect (editor->priv->object,
						     editor->priv->notify_id);
			editor->priv->notify_id = 0;
		}
		g_object_unref (editor->priv->object);
		editor->priv->object = NULL;
	}

	G_OBJECT_CLASS (rb_object_property_editor_parent_class)->dispose (object);
}
