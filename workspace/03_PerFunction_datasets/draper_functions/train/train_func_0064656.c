initialize()
{
	hud_anim_init(&Monitor_static, position[0] + Viewport_offsets[0], position[1] + Viewport_offsets[1], NOX(static_fname));

	for(int i = 0; i < NUM_TBOX_FLASH_TIMERS; i++) {
		initFlashTimer(i);
	}

	HudGauge::initialize();
}
