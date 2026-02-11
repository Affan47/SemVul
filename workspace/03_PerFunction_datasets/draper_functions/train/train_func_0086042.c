gdm_host_chooser_widget_get_host (GdmHostChooserWidget *widget)
{
        GdmChooserHost *host;

        g_return_val_if_fail (GDM_IS_HOST_CHOOSER_WIDGET (widget), NULL);

        host = NULL;
        if (widget->priv->current_host != NULL) {
                host = g_object_ref (widget->priv->current_host);
        }

        return host;
}
