gtk_scroll_frame_destroy (GtkObject *object)
{
	GtkScrollFrame *sf;
	ScrollFramePrivate *priv;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GTK_IS_SCROLL_FRAME (object));

	sf = GTK_SCROLL_FRAME (object);
	priv = sf->priv;

	gtk_widget_unparent (priv->hsb);
	gtk_widget_unparent (priv->vsb);
	gtk_widget_destroy (priv->hsb);
	gtk_widget_destroy (priv->vsb);

	if (GTK_OBJECT_CLASS (parent_class)->destroy)
		(* GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}
