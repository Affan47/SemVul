vxlan_fan_add_map(struct vxlan_dev *vxlan, struct ifla_fan_map *map)
{
	__be32 overlay_mask, underlay_mask;
	struct ip_fan_map *fan_map;

	overlay_mask = inet_make_mask(map->overlay_prefix);
	underlay_mask = inet_make_mask(map->underlay_prefix);

	netdev_dbg(vxlan->dev, "vfam: map: o %x/%d u %x/%d om %x um %x\n",
		   map->overlay, map->overlay_prefix,
		   map->underlay, map->underlay_prefix,
		   overlay_mask, underlay_mask);

	if ((map->overlay & ~overlay_mask) || (map->underlay & ~underlay_mask))
		return -EINVAL;

	if (!(map->overlay & overlay_mask) && (map->underlay & underlay_mask))
		return -EINVAL;


	if (!map->overlay && !map->underlay) {
		vxlan_fan_flush_map(vxlan);
		return 0;
	}


	if (!map->underlay)
		return vxlan_fan_del_map(vxlan, map->overlay);

	if (vxlan_fan_find_map(vxlan, map->overlay))
		return -EEXIST;

	fan_map = kmalloc(sizeof(*fan_map), GFP_KERNEL);
	fan_map->underlay = map->underlay;
	fan_map->overlay = map->overlay;
	fan_map->underlay_prefix = map->underlay_prefix;
	fan_map->overlay_mask = ntohl(overlay_mask);
	fan_map->overlay_prefix = map->overlay_prefix;

	list_add_tail_rcu(&fan_map->list, &vxlan->fan.fan_maps);

	return 0;
}
