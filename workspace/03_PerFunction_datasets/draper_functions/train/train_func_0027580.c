GetModuleInformation (gpointer process, gpointer module,
			       WapiModuleInfo *modinfo, guint32 size)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	pid_t pid;
#if !defined(__OpenBSD__) && !defined(PLATFORM_MACOSX)
	FILE *fp;
#endif
	GSList *mods = NULL;
	WapiProcModule *found_module;
	guint32 count;
	int i;
	gboolean ret = FALSE;
	gchar *proc_name = NULL;

	mono_once (&process_current_once, process_set_current);

	DEBUG ("%s: Getting module info, process handle %p module %p",
		   __func__, process, module);

	if (modinfo == NULL || size < sizeof(WapiModuleInfo)) {
		return(FALSE);
	}

	if ((GPOINTER_TO_UINT (process) & _WAPI_PROCESS_UNHANDLED) == _WAPI_PROCESS_UNHANDLED) {

		pid = (pid_t)(GPOINTER_TO_UINT (process) & _WAPI_PROCESS_UNHANDLED_PID_MASK);
		proc_name = get_process_name_from_proc (pid);
	} else {
		ok = _wapi_lookup_handle (process, WAPI_HANDLE_PROCESS,
					  (gpointer *)&process_handle);
		if (ok == FALSE) {
			DEBUG ("%s: Can't find process %p", __func__,
				   process);

			return(FALSE);
		}
		pid = process_handle->id;
		proc_name = g_strdup (process_handle->proc_name);
	}

#if defined(PLATFORM_MACOSX) || defined(__OpenBSD__) || defined(__HAIKU__)
	{
		mods = load_modules ();
#else

	if ((fp = open_process_map (pid, "r")) == NULL) {


		g_free (proc_name);
		return(FALSE);
	} else {
		mods = load_modules (fp);
		fclose (fp);
#endif
		count = g_slist_length (mods);


		for (i = 0; i < count; i++) {
			found_module = (WapiProcModule *)g_slist_nth_data (mods, i);
			if ( ret == FALSE &&
			     ((module == NULL && match_procname_to_modulename (proc_name, found_module->filename)) ||
			      (module != NULL && found_module->address_start == module))) {
				modinfo->lpBaseOfDll = found_module->address_start;
				modinfo->SizeOfImage = (gsize)(found_module->address_end) - (gsize)(found_module->address_start);
				modinfo->EntryPoint = found_module->address_offset;
				ret = TRUE;
			}

			free_procmodule (found_module);
		}

		g_slist_free (mods);
		g_free (proc_name);
	}

	return(ret);
}
