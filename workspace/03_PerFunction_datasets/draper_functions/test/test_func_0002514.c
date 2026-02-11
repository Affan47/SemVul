gw_dm_is_disk_in_drive ( const gchar *drive_path)
{


	gboolean result = FALSE;
#if defined ( OS_LINUX) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	FILE *tab = NULL;
	struct mntent *partition = NULL;
	gchar *device_path = NULL;
	struct stat statbuf;
	guint fic;
#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
	guint errmode;
	DWORD max_file_len;
	DWORD system_flags;
#endif


#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( drive_path != NULL )
	{

#if defined ( OS_LINUX)


		if ( (tab = setmntent ( "/etc/mtab", "r")) != NULL )
		{
			while ( ((partition = getmntent ( tab)) != NULL) && (device_path == NULL))
			{
				if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
				{
					device_path = g_strdup ( partition->mnt_fsname);
				}
			}


			endmntent ( tab);
		}

		if ( device_path == NULL )
		{

			if ( (tab = setmntent ( "/etc/fstab", "r")) != NULL )
			{
				while ( ((partition = getmntent ( tab)) != NULL) && (device_path == NULL))
				{
					if ( (partition->mnt_dir != NULL) && (strcmp ( partition->mnt_dir, drive_path) == 0) )
					{
						device_path = g_strdup ( partition->mnt_fsname);
					}
				}


				endmntent ( tab);
			}
		}

		if ( device_path != NULL )
		{

			if ( stat ( device_path, &statbuf) != -1 )
			{

				if ( !S_ISREG ( statbuf.st_mode) )
				{

					if ( access ( device_path, R_OK) == 0 )
					{

						if ( ( fic = open ( device_path, O_RDONLY ) ) != -1 )
						{
							result = TRUE;
						}


						close ( fic);
					}
				}
			}

			g_free ( device_path);
		}

#elif defined ( OS_WIN32) || defined ( OS_CYGWIN)
		errmode = SetErrorMode ( SEM_FAILCRITICALERRORS);
		result = GetVolumeInformation ( drive_path, NULL, 0, NULL, &max_file_len, &system_flags, NULL, 0);
		SetErrorMode ( errmode);
#endif
	}

#ifdef GW_DEBUG_DATA_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "%s is %savailable", drive_path,result?"":"un");
#endif

	return result;
}
