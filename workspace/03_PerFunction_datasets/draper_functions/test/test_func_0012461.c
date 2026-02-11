ves_icall_System_Threading_Monitor_Monitor_test_synchronised (MonoObject *obj)
{
	LockWord lw;

	LOCK_DEBUG (g_message("%s: (%d) Testing if %p is owned by any thread", __func__, mono_thread_info_get_small_id (), obj));

	lw.sync = obj->synchronisation;

	if (lock_word_is_flat (lw)) {
		return !lock_word_is_free (lw);
	} else if (lock_word_is_inflated (lw)) {
		return mon_status_get_owner (lock_word_get_inflated_lock (lw)->status) != 0;
	}

	return FALSE;
}
