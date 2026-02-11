print_a1(const char *val)
{
	if (sys) {
		if (strcmp(sys, "open") == 0)
			return print_open_flags(val);
		else if (strcmp(sys, "chmod") == 0)
			return print_mode_short(val);
		else if (strcmp(sys, "fchmod") == 0)
			return print_mode_short(val);
		else if (strstr(sys, "chown"))
			return print_uid(val, 16);
		else if (strcmp(sys, "setreuid") == 0)
			return print_uid(val, 16);
		else if (strcmp(sys, "setresuid") == 0)
			return print_uid(val, 16);
		else if (strcmp(sys, "setregid") == 0)
			return print_gid(val, 16);
		else if (strcmp(sys, "setresgid") == 0)
			return print_gid(val, 16);
		else if (strcmp(sys, "kill") == 0)
			return print_signals(val, 16);
		else if (strcmp(sys, "tkill") == 0)
			return print_signals(val, 16);
		else if (strcmp(sys, "mkdir") == 0)
			return print_mode_short(val);
		else if (strcmp(sys, "creat") == 0)
			return print_mode_short(val);
		else if (strcmp(sys, "access") == 0)
			return print_access(val);
		else if (strncmp(sys, "fcntl", 5) == 0)
			return print_fcntl(val);
		else if (strcmp(sys, "mknod") == 0)
			return print_mode(val, 16);
		else if (strcmp(sys, "socket") == 0)
			return print_socket_type(val);
		else goto normal;
	} else
normal:
		printf("0x%s ", val);
}
