isc___errno2result(int posixerrno, const char *file, unsigned int line) {
	char strbuf[ISC_STRERRORSIZE];

	switch (posixerrno) {
	case ENOTDIR:
	case ELOOP:
	case EINVAL:
	case ENAMETOOLONG:
	case EBADF:
		return (ISC_R_INVALIDFILE);
	case ENOENT:
		return (ISC_R_FILENOTFOUND);
	case EACCES:
	case EPERM:
		return (ISC_R_NOPERM);
	case EEXIST:
		return (ISC_R_FILEEXISTS);
	case EIO:
		return (ISC_R_IOERROR);
	case ENOMEM:
		return (ISC_R_NOMEMORY);
	case ENFILE:
	case EMFILE:
		return (ISC_R_TOOMANYOPENFILES);
#ifdef EOVERFLOW
	case EOVERFLOW:
		return (ISC_R_RANGE);
#endif
	case EPIPE:
#ifdef ECONNRESET
	case ECONNRESET:
#endif
#ifdef ECONNABORTED
	case ECONNABORTED:
#endif
		return (ISC_R_CONNECTIONRESET);
#ifdef ENOTCONN
	case ENOTCONN:
		return (ISC_R_NOTCONNECTED);
#endif
#ifdef ETIMEDOUT
	case ETIMEDOUT:
		return (ISC_R_TIMEDOUT);
#endif
#ifdef ENOBUFS
	case ENOBUFS:
		return (ISC_R_NORESOURCES);
#endif
#ifdef EAFNOSUPPORT
	case EAFNOSUPPORT:
		return (ISC_R_FAMILYNOSUPPORT);
#endif
#ifdef ENETDOWN
	case ENETDOWN:
		return (ISC_R_NETDOWN);
#endif
#ifdef EHOSTDOWN
	case EHOSTDOWN:
		return (ISC_R_HOSTDOWN);
#endif
#ifdef ENETUNREACH
	case ENETUNREACH:
		return (ISC_R_NETUNREACH);
#endif
#ifdef EHOSTUNREACH
	case EHOSTUNREACH:
		return (ISC_R_HOSTUNREACH);
#endif
#ifdef EADDRINUSE
	case EADDRINUSE:
		return (ISC_R_ADDRINUSE);
#endif
	case EADDRNOTAVAIL:
		return (ISC_R_ADDRNOTAVAIL);
	case ECONNREFUSED:
		return (ISC_R_CONNREFUSED);
	default:
		isc__strerror(posixerrno, strbuf, sizeof(strbuf));
		UNEXPECTED_ERROR(file, line, "unable to convert errno "
				 "to isc_result: %d: %s",
				 posixerrno, strbuf);


		return (ISC_R_UNEXPECTED);
	}
}
