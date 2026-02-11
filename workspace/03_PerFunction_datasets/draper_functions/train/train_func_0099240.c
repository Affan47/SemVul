gdbstub_state(struct kgdb_state *ks, char *cmd)
{
	int error;

	switch (cmd[0]) {
	case 'e':
		error = kgdb_arch_handle_exception(ks->ex_vector,
						   ks->signo,
						   ks->err_code,
						   remcom_in_buffer,
						   remcom_out_buffer,
						   ks->linux_regs);
		return error;
	case 's':
	case 'c':
		strcpy(remcom_in_buffer, cmd);
		return 0;
	case '$':
		strcpy(remcom_in_buffer, cmd);
		gdbstub_use_prev_in_buf = strlen(remcom_in_buffer);
		gdbstub_prev_in_buf_pos = 0;
		return 0;
	}
	dbg_io_ops->write_char('+');
	put_packet(remcom_out_buffer);
	return 0;
}
