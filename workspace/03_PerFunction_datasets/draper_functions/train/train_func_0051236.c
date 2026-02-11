vga_switcheroo_show(struct seq_file *m, void *v)
{
	struct vga_switcheroo_client *client;
	int i = 0;

	mutex_lock(&vgasr_mutex);
	list_for_each_entry(client, &vgasr_priv.clients, list) {
		seq_printf(m, "%d:%s%s:%c:%s%s:%s\n", i,
			   client_id(client) == VGA_SWITCHEROO_DIS ? "DIS" :
								     "IGD",
			   client_is_vga(client) ? "" : "-Audio",
			   client->active ? '+' : ' ',
			   client->driver_power_control ? "Dyn" : "",
			   client->pwr_state ? "Pwr" : "Off",
			   pci_name(client->pdev));
		i++;
	}
	mutex_unlock(&vgasr_mutex);
	return 0;
}
