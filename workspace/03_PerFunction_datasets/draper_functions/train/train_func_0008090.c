rt2x00lib_set_if_combinations(struct rt2x00_dev *rt2x00dev)
{
	struct ieee80211_iface_limit *if_limit;
	struct ieee80211_iface_combination *if_combination;

	if (rt2x00dev->ops->max_ap_intf < 2)
		return;


	if_limit = &rt2x00dev->if_limits_ap;
	if_limit->max = rt2x00dev->ops->max_ap_intf;
	if_limit->types = BIT(NL80211_IFTYPE_AP);
#ifdef CONFIG_MAC80211_MESH
	if_limit->types |= BIT(NL80211_IFTYPE_MESH_POINT);
#endif


	if_combination = &rt2x00dev->if_combinations[IF_COMB_AP];
	if_combination->limits = if_limit;
	if_combination->n_limits = 1;
	if_combination->max_interfaces = if_limit->max;
	if_combination->num_different_channels = 1;


	rt2x00dev->hw->wiphy->iface_combinations = rt2x00dev->if_combinations;
	rt2x00dev->hw->wiphy->n_iface_combinations = 1;
}
