_elf_output(Elf *elf, int fd, size_t len, off_t (*_elf_write)(Elf*, char*, size_t)) {
    char *buf;
    off_t err;

    elf_assert(len);
#if HAVE_FTRUNCATE
    ftruncate(fd, 0);
#endif
#if HAVE_MMAP


#if HAVE_FTRUNCATE
    lseek(fd, (off_t)len, SEEK_SET);
    if (ftruncate(fd, len)) {
#else
    {
#endif
	if (lseek(fd, (off_t)len - 1, SEEK_SET) != (off_t)len - 1) {
	    seterr(ERROR_IO_SEEK);
	    return -1;
	}
	if (xwrite(fd, "", 1)) {
	    seterr(ERROR_IO_WRITE);
	    return -1;
	}
    }
    buf = (void*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf != (char*)-1) {
	if ((char)_elf_fill && !(elf->e_elf_flags & ELF_F_LAYOUT)) {
	    memset(buf, _elf_fill, len);
	}
	err = _elf_write(elf, buf, len);
	munmap(buf, len);
	return err;
    }
#endif
    if (!(buf = (char*)malloc(len))) {
	seterr(ERROR_MEM_OUTBUF);
	return -1;
    }
    memset(buf, _elf_fill, len);
    err = _elf_write(elf, buf, len);
    if (err != -1 && (size_t)err == len) {
	if (lseek(fd, (off_t)0, SEEK_SET)) {
	    seterr(ERROR_IO_SEEK);
	    err = -1;
	}
	else if (xwrite(fd, buf, len)) {
	    seterr(ERROR_IO_WRITE);
	    err = -1;
	}
    }
    free(buf);
    return err;
}
