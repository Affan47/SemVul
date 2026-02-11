_gcr_initialize_library (void)
{
	static gint gcr_initialize = 0;

	if (g_atomic_int_add (&gcr_initialize, 1) == 0)
		return;


	egg_libgcrypt_initialize ();

	_gcr_debug ("initialized library");
}
