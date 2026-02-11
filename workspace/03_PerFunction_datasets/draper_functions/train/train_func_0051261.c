abi_widget_set_zoom_percentage (AbiWidget * w, guint32 zoom)
{
	UT_return_val_if_fail ( w != NULL, FALSE );
	UT_return_val_if_fail ( IS_ABI_WIDGET(w), FALSE );
	UT_return_val_if_fail ( w->priv->m_pFrame, FALSE );

	w->priv->m_pFrame->setZoomType(XAP_Frame::z_PERCENT);
	w->priv->m_pFrame->quickZoom(zoom);
	return TRUE;
}
