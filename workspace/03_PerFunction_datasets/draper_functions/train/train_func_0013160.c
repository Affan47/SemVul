vga_switchto_stage1(struct vga_switcheroo_client *new_client)
{
	struct vga_switcheroo_client *active;

	active = find_active_client(&vgasr_priv.clients);
	if (!active)
		return 0;

	if (new_client->pwr_state == VGA_SWITCHEROO_OFF)
		vga_switchon(new_client);

	vga_set_default_device(new_client->pdev);
	return 0;
}
