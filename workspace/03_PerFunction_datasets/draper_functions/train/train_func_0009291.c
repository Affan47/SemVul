tell_parent(enum info_type type)
{
	if (control_fd != -1)
		write_all(control_fd, &type, sizeof(type));
}
