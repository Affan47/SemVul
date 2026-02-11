mono_double_ParseImpl (char *ptr, double *result)
{
	gchar *endptr = NULL;
	*result = 0.0;

	MONO_ARCH_SAVE_REGS;

#ifdef __arm__
	if (*ptr)
		*result = strtod (ptr, &endptr);
#else
	if (*ptr){

		EnterCriticalSection (&mono_strtod_mutex);
		*result = mono_strtod (ptr, &endptr);
		LeaveCriticalSection (&mono_strtod_mutex);
	}
#endif

	if (!*ptr || (endptr && *endptr))
		return FALSE;

	return TRUE;
}
