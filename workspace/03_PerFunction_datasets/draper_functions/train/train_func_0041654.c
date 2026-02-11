on_forward_button_clicked(GtkToolButton * btn, DevhelpPlugin *self)
{
	g_return_if_fail(DEVHELP_IS_PLUGIN(self));
	webkit_web_view_go_forward(WEBKIT_WEB_VIEW(self->priv->webview));
}
