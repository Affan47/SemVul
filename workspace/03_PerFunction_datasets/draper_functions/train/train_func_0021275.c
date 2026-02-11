e_attachment_view_set_dragging (EAttachmentView *view,
                                gboolean dragging)
{
	EAttachmentViewPrivate *priv;

	g_return_if_fail (E_IS_ATTACHMENT_VIEW (view));

	priv = e_attachment_view_get_private (view);

	priv->dragging = dragging;

	g_object_notify (G_OBJECT (view), "dragging");
}
