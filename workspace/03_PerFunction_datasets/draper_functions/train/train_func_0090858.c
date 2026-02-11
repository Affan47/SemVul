_gedit_app_set_lockdown_bit (GeditApp          *app,
			     GeditLockdownMask  bit,
			     gboolean           value)
{
	g_return_if_fail (GEDIT_IS_APP (app));

	if (value)
		app->priv->lockdown |= bit;
	else
		app->priv->lockdown &= ~bit;

	app_lockdown_changed (app);
}
