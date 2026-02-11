panel_action_get_is_disabled (PanelActionButtonType type)
{
	g_return_val_if_fail (type > PANEL_ACTION_NONE && type < PANEL_ACTION_LAST, FALSE);

	if (panel_action_get_is_deprecated (type))
		return TRUE;

	if (actions [type].is_disabled)
		return actions [type].is_disabled ();

	return FALSE;
}
