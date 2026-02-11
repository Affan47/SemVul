nemo_icon_container_accessible_action_set_description (AtkAction *accessible,
							   int i,
							   const char *description)
{
	NemoIconContainerAccessiblePrivate *priv;

	g_assert (i < LAST_ACTION);

	priv = accessible_get_priv (ATK_OBJECT (accessible));

	if (priv->action_descriptions[i]) {
		g_free (priv->action_descriptions[i]);
	}
	priv->action_descriptions[i] = g_strdup (description);

	return FALSE;
}
