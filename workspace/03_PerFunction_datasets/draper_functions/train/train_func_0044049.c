nm_setting_vlan_clear_priorities (NMSettingVlan *setting, NMVlanPriorityMap map)
{
	GSList *list = NULL;

	g_return_if_fail (NM_IS_SETTING_VLAN (setting));
	g_return_if_fail (map == NM_VLAN_INGRESS_MAP || map == NM_VLAN_EGRESS_MAP);

	list = get_map (setting, map);
	nm_utils_slist_free (list, g_free);
	set_map (setting, map, NULL);
}
