gnm_dao_is_finite (GnmDao *gdao)
{
	int grp_val;

	g_return_val_if_fail (gdao != NULL, FALSE);

	grp_val = gnm_gui_group_value (gdao->gui, dao_group);
	return ((grp_val == 2) || (grp_val == 3));
}
