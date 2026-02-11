createdir4nick (u_char *nick)
{
	if (nick && nick[0])
	{
		char dir[1024];
		strcpy (dir, chatlogdir);
		if (dir[strlen (dir)-1]!='/')
			strcat (dir,"/");
		strcat (dir,(char *) nick);
#ifdef WIN32
		mkdir (dir);
#else
		mkdir (dir,0700);
#endif
	}
	return 0;
}
