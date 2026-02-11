pblimage_check_params(struct image_tool_params *params)
{
	FILE *fp_uboot;
	int fd;
	struct stat st;

	if (!params)
		return EXIT_FAILURE;

	fp_uboot = fopen(params->datafile, "r");
	if (fp_uboot == NULL) {
		printf("Error: %s open failed\n", params->datafile);
		exit(EXIT_FAILURE);
	}
	fd = fileno(fp_uboot);

	if (fstat(fd, &st) == -1) {
		printf("Error: Could not determine u-boot image size. %s\n",
		       strerror(errno));
		exit(EXIT_FAILURE);
	}


	uboot_size = roundup(st.st_size, 64);

	if (params->arch == IH_ARCH_ARM) {
		arch_flag = IH_ARCH_ARM;
		pbi_crc_cmd1 = 0x61;
		pbi_crc_cmd2 = 0;
		pbl_cmd_initaddr = params->addr & PBL_ADDR_24BIT_MASK;
		pbl_cmd_initaddr |= PBL_ACS_CONT_CMD;
		pbl_cmd_initaddr |= uboot_size;
		pbl_end_cmd[0] = 0x09610000;
		pbl_end_cmd[1] = 0x00000000;
		pbl_end_cmd[2] = 0x096100c0;
		pbl_end_cmd[3] = 0x00000000;
	} else if (params->arch == IH_ARCH_PPC) {
		arch_flag = IH_ARCH_PPC;
		pbi_crc_cmd1 = 0x13;
		pbi_crc_cmd2 = 0x80;
		pbl_cmd_initaddr = 0x82000000;
		pbl_end_cmd[0] = 0x09138000;
		pbl_end_cmd[1] = 0x00000000;
		pbl_end_cmd[2] = 0x091380c0;
		pbl_end_cmd[3] = 0x00000000;
	}

	next_pbl_cmd = pbl_cmd_initaddr;
	return 0;
}
