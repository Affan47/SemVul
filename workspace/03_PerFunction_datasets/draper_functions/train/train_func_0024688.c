rocker_port_vlans_add(struct rocker_port *rocker_port,
				 struct switchdev_trans *trans,
				 const struct switchdev_obj_port_vlan *vlan)
{
	u16 vid;
	int err;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		err = rocker_port_vlan_add(rocker_port, trans,
					   vid, vlan->flags);
		if (err)
			return err;
	}

	return 0;
}
