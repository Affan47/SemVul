fr_command_rar_list (FrCommand  *comm)
{
	rar_check_multi_volume (comm);

	fr_process_set_out_line_func (comm->process, process_line, comm);

	if (have_rar ())
		fr_process_begin_command (comm->process, "rar");
	else
		fr_process_begin_command (comm->process, "unrar");
	fr_process_set_begin_func (comm->process, list__begin, comm);
	fr_process_add_arg (comm->process, "v");
	fr_process_add_arg (comm->process, "-c-");
	fr_process_add_arg (comm->process, "-v");

	add_password_arg (comm, FR_ARCHIVE (comm)->password, TRUE);


	fr_process_add_arg (comm->process, "--");

	fr_process_add_arg (comm->process, comm->filename);
	fr_process_end_command (comm->process);

	return TRUE;
}
