get_local_user()
{


#ifdef G_OS_WIN32
	return NULL;
#else
  	struct passwd *pw;
  	const static gchar* localuser = NULL;

	if(localuser) return localuser;

  	localuser = g_getenv("USER");
  	if( (localuser == NULL) || ((pw = getpwnam(localuser)) && (pw->pw_uid != getuid())) )
  	{
		if ( (pw = getpwuid(getuid())))
			localuser = g_strdup(pw->pw_name);
		else
			localuser = NULL;
  	}
  return localuser;
#endif
}
