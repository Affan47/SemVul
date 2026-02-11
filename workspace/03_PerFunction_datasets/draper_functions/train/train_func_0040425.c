vga_switchoff(struct vga_switcheroo_client *client)
{
	if (client->driver_power_control)
		return 0;

	client->ops->set_gpu_state(client->pdev, VGA_SWITCHEROO_OFF);
	if (vgasr_priv.handler->power_state)
		vgasr_priv.handler->power_state(client->id, VGA_SWITCHEROO_OFF);
	client->pwr_state = VGA_SWITCHEROO_OFF;
	return 0;
}
