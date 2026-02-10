ves_icall_System_Diagnostics_Process_WaitForInputIdle_internal (MonoObject *this_obj, HANDLE process, gint32 ms)
{
	guint32 ret;

	if(ms<0) {

		ret=WaitForInputIdle (process, INFINITE);
	} else {
		ret=WaitForInputIdle (process, ms);
	}

	return (ret) ? FALSE : TRUE;
}
