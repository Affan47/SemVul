dcc_close (struct DCC *dcc, int dccstat, int destroy)
{
	if (dcc->wiotag)
	{
		fe_input_remove (dcc->wiotag);
		dcc->wiotag = 0;
	}

	if (dcc->iotag)
	{
		fe_input_remove (dcc->iotag);
		dcc->iotag = 0;
	}

	if (dcc->sok != -1)
	{
		closesocket (dcc->sok);
		dcc->sok = -1;
	}

	dcc_remove_from_sum (dcc);

	if (dcc->fp != -1)
	{
		close (dcc->fp);
		dcc->fp = -1;

		if(dccstat == STAT_DONE)
		{


			if(dcc->type == TYPE_RECV)
			{

				move_file (prefs.hex_dcc_dir, prefs.hex_dcc_completed_dir,
									 file_part (dcc->destfile), prefs.hex_dcc_permissions);
			}

		}
	}

	dcc->dccstat = dccstat;
	if (dcc->dccchat)
	{
		free (dcc->dccchat);
		dcc->dccchat = NULL;
	}

	if (destroy)
	{
		dcc_list = g_slist_remove (dcc_list, dcc);
		fe_dcc_remove (dcc);
		if (dcc->proxy)
			free (dcc->proxy);
		if (dcc->file)
			free (dcc->file);
		if (dcc->destfile)
			g_free (dcc->destfile);
		free (dcc->nick);
		free (dcc);
		return;
	}

	fe_dcc_update (dcc);
}
