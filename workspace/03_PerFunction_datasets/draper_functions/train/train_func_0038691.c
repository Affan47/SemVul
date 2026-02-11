ensure_static_blob_filled (void)
{
	if (random_blob [0] == 0) {
		guint i;
		for (i = 0; i < RANDOM_BLOB_SIZE; i++) {
			random_blob [i]	= g_random_int_range (1, 255);

		}
#ifdef G_OS_WIN32
		VirtualLock (random_blob, sizeof (gchar) * RANDOM_BLOB_SIZE);
#else
#ifdef USE_MLOCK
		mlock (random_blob, sizeof (gchar) * RANDOM_BLOB_SIZE);
#endif
#endif
	}
}
