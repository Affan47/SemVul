sgen_is_thread_in_current_stw (SgenThreadInfo *info)
{


	if (info->client_info.gc_disabled) {
		return FALSE;
	}


	if (info->client_info.skip) {
		return FALSE;
	}


	if (info == mono_thread_info_current ()) {
		return FALSE;
	}


	if (sgen_thread_pool_is_thread_pool_thread (mono_thread_info_get_tid (info))) {
		return FALSE;
	}


	if (!mono_thread_info_is_live (info)) {
		return FALSE;
	}

	return TRUE;
}
