IoObject_platform(IoObject *self, IoObject *locals, IoMessage *m)
{


	char *platform = "Unknown";

#if defined(__CYGWIN__)

	platform = "cygwin";

#elif defined(__MINGW32__)

	platform = "mingw";

#elif defined(_WIN32)

	OSVERSIONINFO os;

	os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx(&os);

	switch(os.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_WINDOWS:
			switch(os.dwMinorVersion)
			{
				case 0:
					platform = "Windows 95";
					break;
				case 10:
					platform = "Windows 98";
					break;
				case 90:
					platform = "Windows ME";
					break;
				default:
					platform = "Windows 9X";
					break;
			}
			break;

		case VER_PLATFORM_WIN32_NT:
			if (os.dwMajorVersion == 3 || os.dwMajorVersion == 4)
			{
				platform = "Windows NT";
			}
			else if (os.dwMajorVersion == 5)
			{
				switch(os.dwMinorVersion)
				{
					case 0:
						platform = "Windows 2000";
						break;
					case 1:
						platform = "Windows XP";
						break;
					default:
						platform = "Windows";
						break;
				}
			}
			else
			{
				platform = "Windows";
			}
			break;

		default: platform = "Windows";
	}

#elif defined(unix) || defined(__APPLE__) || defined(__NetBSD__)

	struct utsname os;
	int ret = uname(&os);

	if (ret == 0)
	{
		platform = os.sysname;
	}
#endif

	return IoState_symbolWithCString_(IOSTATE, platform);
}
