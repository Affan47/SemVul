read_executable(struct svc_req *req, backend_statstruct buf)
{
    int have_exec = 0;

    if (is_owner(buf.st_uid, req)) {
	if (!(buf.st_mode & S_IRUSR) && (buf.st_mode & S_IXUSR))
	    have_exec = 1;
    } else if (has_group(buf.st_gid, req)) {
	if (!(buf.st_mode & S_IRGRP) && (buf.st_mode & S_IXGRP))
	    have_exec = 1;
    } else {
	if (!(buf.st_mode & S_IROTH) && (buf.st_mode & S_IXOTH))
	    have_exec = 1;
    }

    if (have_exec) {
	backend_setegid(0);
	backend_seteuid(0);
    }
}
