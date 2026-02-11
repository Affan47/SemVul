ves_icall_System_Security_Cryptography_RNGCryptoServiceProvider_RngOpen (void)
{
	if (egd || (file >= 0))
		return TRUE;

#if defined (NAME_DEV_URANDOM)
	file = open (NAME_DEV_URANDOM, O_RDONLY);
#endif

#if defined (NAME_DEV_RANDOM)
	if (file < 0)
		file = open (NAME_DEV_RANDOM, O_RDONLY);
#endif

	if (file < 0) {
		const char *socket_path = g_getenv("MONO_EGD_SOCKET");
		egd = (socket_path != NULL);
	}


	return TRUE;
}
