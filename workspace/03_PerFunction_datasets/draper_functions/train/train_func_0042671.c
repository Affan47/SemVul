DtsSetDecStat(bool bDecOpen, pid_t PID)
{
	if (bDecOpen == true)
		bc_dil_glob_ptr->g_nProcID = PID;
	else
		bc_dil_glob_ptr->g_nProcID = 0;

	bc_dil_glob_ptr->g_bDecOpened = bDecOpen;
}
