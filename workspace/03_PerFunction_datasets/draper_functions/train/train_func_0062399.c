xc_core_strtab(uint32_t index, char *buf)
{
	off_t offset;
	int i;

	offset = xd->xc_core.elf_strtab_offset + index;

	if (lseek(xd->xfd, offset, SEEK_SET) != offset)
		error(FATAL,
		    "xc_core_strtab: cannot seek to Elf64_Shdr\n");

	BZERO(buf, BUFSIZE);
	i = 0;

	while (read(xd->xfd, &buf[i], sizeof(char)) == sizeof(char)) {
		if (buf[i] == NULLCHAR)
			break;
		i++;
	}

	return buf;
}
