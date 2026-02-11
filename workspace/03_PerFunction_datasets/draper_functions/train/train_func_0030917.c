getport(port, sinp)
int port;
struct sockaddr_in *sinp;
{
	if (port < 0 || port > MAXUTYPE(u_short)) return(seterrno(EINVAL));
	sinp -> sin_port = htons(port);

	return(0);
}
