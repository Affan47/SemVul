etcta_get_name (AtkObject *obj)
{
	ETableClickToAdd * etcta;

	g_return_val_if_fail (GAL_A11Y_IS_E_TABLE_CLICK_TO_ADD (obj), NULL);

	etcta = E_TABLE_CLICK_TO_ADD (
		atk_gobject_accessible_get_object (
		ATK_GOBJECT_ACCESSIBLE (obj)));
	if (etcta && etcta->message != NULL)
		return etcta->message;

	return _("click to add");
}
