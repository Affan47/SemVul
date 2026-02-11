perl_process_fill_hash(HV *hv, PROCESS_REC *process)
{
	hv_store(hv, "id", 2, newSViv(process->id), 0);
	hv_store(hv, "name", 4, new_pv(process->name), 0);
	hv_store(hv, "args", 4, new_pv(process->args), 0);

	hv_store(hv, "pid", 3, newSViv(process->pid), 0);
	hv_store(hv, "target", 6, new_pv(process->target), 0);
	if (process->target_win != NULL) {
		hv_store(hv, "target_win", 10,
			 plain_bless(process->target_win, "Irssi::UI::Window"), 0);
	}
	hv_store(hv, "shell", 5, newSViv(process->shell), 0);
	hv_store(hv, "notice", 6, newSViv(process->notice), 0);
	hv_store(hv, "silent", 6, newSViv(process->silent), 0);
}
