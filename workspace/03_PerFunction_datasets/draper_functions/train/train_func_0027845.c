ves_icall_System_Security_Principal_WindowsIdentity_GetTokenName (gpointer token)
{
	MonoString *result = NULL;
	gunichar2 *uniname = NULL;
	gint32 size = 0;

#ifdef HOST_WIN32
	MONO_ARCH_SAVE_REGS;

	GetTokenInformation (token, TokenUser, NULL, size, (PDWORD)&size);
	if (size > 0) {
		TOKEN_USER *tu = g_malloc0 (size);
		if (GetTokenInformation (token, TokenUser, tu, size, (PDWORD)&size)) {
			uniname = GetSidName (NULL, tu->User.Sid, &size);
		}
		g_free (tu);
	}
#else
	gchar *uname = GetTokenName ((uid_t) GPOINTER_TO_INT (token));

	MONO_ARCH_SAVE_REGS;

	if (uname) {
		size = strlen (uname);
		uniname = g_utf8_to_utf16 (uname, size, NULL, NULL, NULL);
		g_free (uname);
	}
#endif

	if (size > 0) {
		result = mono_string_new_utf16 (mono_domain_get (), uniname, size);
	}
	else
		result = mono_string_new (mono_domain_get (), "");

	if (uniname)
		g_free (uniname);

	return result;
}
