bnx2x_admin_app_is_equal(
	struct bnx2x_admin_priority_app_table *app_ent,
	u8 idtype, u16 idval)
{
	if (!app_ent->valid)
		return false;

	switch (idtype) {
	case DCB_APP_IDTYPE_ETHTYPE:
		if (app_ent->traffic_type != TRAFFIC_TYPE_ETH)
			return false;
		break;
	case DCB_APP_IDTYPE_PORTNUM:
		if (app_ent->traffic_type != TRAFFIC_TYPE_PORT)
			return false;
		break;
	default:
		return false;
	}
	if (app_ent->app_id != idval)
		return false;

	return true;
}
