glade_widget_get_signal_model (GladeWidget *widget)
{
	if (!widget->priv->signal_model)
	{
		widget->priv->signal_model = glade_signal_model_new (widget,
                                                         widget->priv->signals);
	}
	return widget->priv->signal_model;
}
