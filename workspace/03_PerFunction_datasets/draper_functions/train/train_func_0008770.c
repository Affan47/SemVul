create()
{


    fxStr templ = file.head(file.nextR(file.length(), '/'));
    templ.append("/TM.faxXXXXXX");
    char* buff = strcpy(new char[templ.length() + 1], templ);
    int fd = Sys::mkstemp(buff);
    if (fd >= 0) {
	writeData(fd);
#if HAS_FCHMOD
	fchmod(fd, mode);
#else
	Sys::chmod(buff, mode);
#endif
#if HAS_FCHOWN
	(void) fchown(fd, UUCPuid, UUCPgid);
#else
	Sys::chown(buff, UUCPuid, UUCPgid);
#endif
	Sys::close(fd);

	locked = (Sys::link(buff, file) == 0);
	Sys::unlink(buff);
    }
    delete [] buff;
    return (locked);
}
