pgstat_get_backend_current_activity(int pid, bool checkUser)
{
	PgBackendStatus *beentry;
	int			i;

	beentry = BackendStatusArray;
	for (i = 1; i <= MaxBackends; i++)
	{


		volatile PgBackendStatus *vbeentry = beentry;
		bool		found;

		for (;;)
		{
			int			save_changecount = vbeentry->st_changecount;

			found = (vbeentry->st_procpid == pid);

			if (save_changecount == vbeentry->st_changecount &&
				(save_changecount & 1) == 0)
				break;


			CHECK_FOR_INTERRUPTS();
		}

		if (found)
		{

			if (checkUser && !superuser() && beentry->st_userid != GetUserId())
				return "<insufficient privilege>";
			else if (*(beentry->st_activity) == '\0')
				return "<command string not enabled>";
			else
				return beentry->st_activity;
		}

		beentry++;
	}


	return "<backend information not available>";
}
