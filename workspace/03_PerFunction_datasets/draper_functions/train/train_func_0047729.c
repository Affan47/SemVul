idifunc_init(void)
{
	diva_os_initialize_spin_lock(&ll_lock, "idifunc");

	if (diva_user_mode_idi_init()) {
		DBG_ERR(("init: init failed."));
		return (0);
	}

	if (!connect_didd()) {
		diva_user_mode_idi_finit();
		DBG_ERR(("init: failed to connect to DIDD."));
		return (0);
	}
	return (1);
}
