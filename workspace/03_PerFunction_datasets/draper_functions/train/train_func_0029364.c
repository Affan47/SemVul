U7mkdir
	(
	const char *dirname,
	int mode
	)
{
	string name = get_system_path(dirname);
#if (defined(MACOSX) || defined(BEOS))

	string::size_type pos = name.find_last_not_of('/');
	if (pos != string::npos)
	  name.resize(pos+1);
#endif
#if defined(WIN32) && defined(UNICODE)
	const char *n = name.c_str();
	int nLen = std::strlen(n)+1;
	LPTSTR lpszT = (LPTSTR) alloca(nLen*2);
	MultiByteToWideChar(CP_ACP, 0, n, -1, lpszT, nLen);
	return CreateDirectory(lpszT, NULL);
#elif defined(WIN32)
	return mkdir(name.c_str());
#else
	return mkdir(name.c_str(), mode);
#endif
}
