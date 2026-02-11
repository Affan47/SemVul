gsm_autostart_app_has_autostart_condition (GsmApp     *app,
                                           const char *condition)
{
        GsmAutostartApp *aapp;

        g_return_val_if_fail (GSM_IS_APP (app), FALSE);
        g_return_val_if_fail (condition != NULL, FALSE);

        aapp = GSM_AUTOSTART_APP (app);

        if (aapp->priv->condition_string == NULL) {
                return FALSE;
        }

        if (strcmp (aapp->priv->condition_string, condition) == 0) {
                return TRUE;
        }

        return FALSE;
}
