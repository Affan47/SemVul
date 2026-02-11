hud_damage_popup_init()
{
	int i;

	Damage_flash_bright = 0;
	Damage_flash_timer =	1;

	for ( i = 0; i < SUBSYSTEM_MAX; i++ ) {
		Pl_hud_subsys_info[i].last_str = 1000.0f;
		Pl_hud_subsys_info[i].flash_duration_timestamp = 1;
		Pl_hud_next_flash_timestamp = 1;
		Pl_hud_is_bright = 0;
	}
}
