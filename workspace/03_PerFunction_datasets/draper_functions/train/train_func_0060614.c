nouveau_dsm_switchto(enum vga_switcheroo_client_id id)
{
	if (!nouveau_dsm_priv.dsm_detected)
		return 0;
	if (id == VGA_SWITCHEROO_IGD)
		return nouveau_dsm_switch_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_STAMINA);
	else
		return nouveau_dsm_switch_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_SPEED);
}
