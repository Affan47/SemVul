parse_vboxrc(void)
{
	struct passwd *userpw;
	streamio_t    *vboxrc;
	char           rcname[PATH_MAX + 1];
	char           rcline[128 + 1];
	char          *cmd;
	char          *arg;

	if ((userpw = getpwuid(getuid())))
	{
		xstrncpy(rcname, userpw->pw_dir, PATH_MAX);
		xstrncat(rcname, "/.vboxrc"    , PATH_MAX);

		if ((vboxrc = streamio_open(rcname)))
		{
			while (streamio_gets(rcline, 128, vboxrc))
			{
				cmd = strtok(rcline, "\t ");
				arg = strtok(NULL  , "\t ");

				if ((cmd) && (arg))
				{
					if (strncasecmp(cmd, "C_", 2) == 0)
					{
						parse_colors(cmd, arg);
					}
					else
					{
						if (strcasecmp(cmd, "USERNAME") == 0)
						{
							xstrncpy(loginname, arg, VBOX_MAX_USERNAME);

							continue;
						}

						if (strcasecmp(cmd, "PASSWORD") == 0)
						{
							xstrncpy(loginpass, arg, VBOX_MAX_PASSWORD);

							continue;
						}

						if (strcasecmp(cmd, "VOLUME") == 0)
						{
							sndvolume = atoi(arg);

							if (sndvolume < 0  ) sndvolume = 0;
							if (sndvolume > 999) sndvolume = 999;
						}
					}
				}
			}

			streamio_close(vboxrc);
		}
	}
}
