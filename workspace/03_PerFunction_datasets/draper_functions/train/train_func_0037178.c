gsm_properties_dialog_dispose (GObject *object)
{
        GsmPropertiesDialog *dialog;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GSM_IS_PROPERTIES_DIALOG (object));

        dialog = GSM_PROPERTIES_DIALOG (object);

        if (dialog->priv->xml != NULL) {
                g_object_unref (dialog->priv->xml);
                dialog->priv->xml = NULL;
        }

        if (dialog->priv->settings != NULL) {
                g_object_unref (dialog->priv->settings);
                dialog->priv->settings = NULL;
        }

        G_OBJECT_CLASS (gsm_properties_dialog_parent_class)->dispose (object);


        if (dialog->priv->manager != NULL) {
                g_object_unref (dialog->priv->manager);
                dialog->priv->manager = NULL;
        }
}
