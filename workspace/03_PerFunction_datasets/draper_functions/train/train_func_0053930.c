e_cal_component_id_hash (const ECalComponentId *id)
{
	guint uid_hash;
	guint rid_hash;

	g_return_val_if_fail (id != NULL, 0);

	uid_hash = g_str_hash (id->uid);
	rid_hash = (id->rid != NULL) ? g_str_hash (id->rid) : 0;

	return uid_hash ^ rid_hash;
}
