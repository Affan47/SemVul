process_open_compare (gpointer handle, gpointer user_data)
{
	pid_t wanted_pid;
	pid_t checking_pid = signal_process_if_gone (handle);

	if (checking_pid == 0) {
		return(FALSE);
	}

	wanted_pid = GPOINTER_TO_UINT (user_data);


	if (checking_pid == wanted_pid &&
	    _wapi_handle_issignalled (handle) == FALSE) {


		return(TRUE);
	} else {
		return(FALSE);
	}
}
