lbs_remove_mesh(struct lbs_private *priv)
{
	struct net_device *mesh_dev;

	mesh_dev = priv->mesh_dev;
	if (!mesh_dev)
		return;

	lbs_deb_enter(LBS_DEB_MESH);
	netif_stop_queue(mesh_dev);
	netif_carrier_off(mesh_dev);
	sysfs_remove_group(&(mesh_dev->dev.kobj), &lbs_mesh_attr_group);
	lbs_persist_config_remove(mesh_dev);
	unregister_netdev(mesh_dev);
	priv->mesh_dev = NULL;
	kfree(mesh_dev->ieee80211_ptr);
	free_netdev(mesh_dev);
	lbs_deb_leave(LBS_DEB_MESH);
}
