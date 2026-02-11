jar_signal(int status, JAR *jar, const char *metafile, char *pathname)
{
    char *errstring = JAR_get_error (status);
    if (jar->signal) {
	(*jar->signal) (status, jar, metafile, pathname, errstring);
	return 0;
    }
    return status;
}
