kgdboc_post_exp_handler(void)
{

	if (!kgdb_connected)
		module_put(THIS_MODULE);
	if (kgdboc_use_kms && dbg_restore_graphics) {
		dbg_restore_graphics = 0;
		con_debug_leave();
	}
	kgdboc_restore_input();
}
