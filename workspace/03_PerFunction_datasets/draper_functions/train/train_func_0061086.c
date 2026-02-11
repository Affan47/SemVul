thunderbolt_shutdown_and_free(struct tb *tb)
{
	struct tb_pci_tunnel *tunnel;
	struct tb_pci_tunnel *n;

	mutex_lock(&tb->lock);


	list_for_each_entry_safe(tunnel, n, &tb->tunnel_list, list) {
		tb_pci_deactivate(tunnel);
		tb_pci_free(tunnel);
	}

	if (tb->root_switch)
		tb_switch_free(tb->root_switch);
	tb->root_switch = NULL;

	if (tb->ctl) {
		tb_ctl_stop(tb->ctl);
		tb_ctl_free(tb->ctl);
	}
	tb->ctl = NULL;
	tb->hotplug_active = false;


	mutex_unlock(&tb->lock);
	if (tb->wq) {
		flush_workqueue(tb->wq);
		destroy_workqueue(tb->wq);
		tb->wq = NULL;
	}
	mutex_destroy(&tb->lock);
	kfree(tb);
}
