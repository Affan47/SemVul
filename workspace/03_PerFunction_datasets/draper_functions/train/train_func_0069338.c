logsrv_addrlen(const struct logsrv *logsrv)
{
	switch (logsrv->u.addr.sa_family) {
	case AF_UNIX:
		return sizeof(logsrv->u.un);
	case AF_INET:
		return sizeof(logsrv->u.in);
	default:
		break;
	}
	return -1;
}
