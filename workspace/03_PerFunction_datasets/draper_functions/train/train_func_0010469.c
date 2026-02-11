setup_linux_bootloader_parameters_high(
	struct kexec_info *info, struct x86_linux_param_header *real_mode,
	unsigned long real_mode_base, unsigned long cmdline_offset,
	const char *cmdline, off_t cmdline_len,
	const char *initrd_buf, off_t initrd_size, int initrd_high)
{
	char *cmdline_ptr;
	unsigned long initrd_base, initrd_addr_max;


	real_mode->loader_type = LOADER_TYPE_KEXEC << 4;


	real_mode->loader_flags = 0;


	if (initrd_high)
		initrd_addr_max = ULONG_MAX;
	else {
		initrd_addr_max = DEFAULT_INITRD_ADDR_MAX;
		if (real_mode->protocol_version >= 0x0203) {
			initrd_addr_max = real_mode->initrd_addr_max;
			dbgprintf("initrd_addr_max is 0x%lx\n",
					 initrd_addr_max);
		}
	}


	if (initrd_buf) {
		initrd_base = add_buffer(info,
			initrd_buf, initrd_size, initrd_size,
			4096, INITRD_BASE, initrd_addr_max, -1);
		dbgprintf("Loaded initrd at 0x%lx size 0x%lx\n", initrd_base,
			initrd_size);
	} else {
		initrd_base = 0;
		initrd_size = 0;
	}


	real_mode->initrd_start = initrd_base & 0xffffffffUL;
	real_mode->initrd_size  = initrd_size & 0xffffffffUL;

	if (real_mode->protocol_version >= 0x020c &&
	    (initrd_base & 0xffffffffUL) != initrd_base)
		real_mode->ext_ramdisk_image = initrd_base >> 32;

	if (real_mode->protocol_version >= 0x020c &&
	    (initrd_size & 0xffffffffUL) != initrd_size)
		real_mode->ext_ramdisk_size = initrd_size >> 32;


		real_mode->cl_magic = CL_MAGIC_VALUE;
		real_mode->cl_offset = cmdline_offset;


	if (real_mode->protocol_version >= 0x0202) {
		unsigned long cmd_line_ptr = real_mode_base + cmdline_offset;

		real_mode->cmd_line_ptr = cmd_line_ptr & 0xffffffffUL;
		if ((real_mode->protocol_version >= 0x020c) &&
		    ((cmd_line_ptr & 0xffffffffUL) != cmd_line_ptr))
			real_mode->ext_cmd_line_ptr = cmd_line_ptr >> 32;
	}


	if (cmdline_len > COMMAND_LINE_SIZE) {
		cmdline_len = COMMAND_LINE_SIZE;
	}
	cmdline_ptr = ((char *)real_mode) + cmdline_offset;
	memcpy(cmdline_ptr, cmdline, cmdline_len);
	cmdline_ptr[cmdline_len - 1] = '\0';
}
