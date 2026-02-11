thunderbolt_resume(struct tb *tb)
{
	struct tb_pci_tunnel *tunnel, *n;
	tb_info(tb, "resuming...\n");
	mutex_lock(&tb->lock);
	tb_ctl_start(tb->ctl);


	tb_switch_reset(tb, 0);

	tb_switch_resume(tb->root_switch);
	tb_free_invalid_tunnels(tb);
	tb_free_unplugged_children(tb->root_switch);
	list_for_each_entry_safe(tunnel, n, &tb->tunnel_list, list)
		tb_pci_restart(tunnel);
	if (!list_empty(&tb->tunnel_list)) {


		tb_info(tb, "tunnels restarted, sleeping for 100ms\n");
		msleep(100);
	}

	tb->hotplug_active = true;
	mutex_unlock(&tb->lock);
	tb_info(tb, "resume finished\n");
}
