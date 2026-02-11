writeConfig()
{
    if (changed && file != "") {
	mode_t omask = umask(022);
	int fd = Sys::open(file, O_WRONLY|O_CREAT, 0644);
	(void) umask(omask);
	if (fd >= 0) {
	    fxStackBuffer buf;
	    writeConfig(buf);
	    u_int cc = buf.getLength();
	    if (Sys::write(fd, buf, cc) != (ssize_t)cc) {
		error("write error: %s", strerror(errno));
		Sys::close(fd);
		return;
	    }
	    (void) ftruncate(fd, cc);
	    Sys::close(fd);
	} else
	    error("open: %m");
	changed = false;
    }
}
