chgsockopt(s, opt)
int s, opt;
{
# if	defined (IPPROTO_IP) && defined (IP_TOS)
	int tos;
# endif
	int n;

	n = 0;
# if	defined (IPPROTO_IP) && defined (IP_TOS)
	switch (opt & SCK_TOSTYPE) {
#  ifdef	IPTOS_LOWDELAY
		case SCK_LOWDELAY:
			tos = IPTOS_LOWDELAY;
			break;
#  endif
#  ifdef	IPTOS_THROUGHPUT
		case SCK_THROUGHPUT:
			tos = IPTOS_THROUGHPUT;
			break;
#  endif
#  ifdef	IPTOS_RELIABILITY
		case SCK_RELIABILITY:
			tos = IPTOS_RELIABILITY;
			break;
#  endif
#  ifdef	IPTOS_MINCOST
		case SCK_MINCOST:
			tos = IPTOS_MINCOST;
			break;
#  endif
		case SCK_NORMAL:
			tos = 0;
			break;
		default:
			tos = -1;
			break;
	}
	if (tos >= 0) {
		if (setsockopt2(s, IPPROTO_IP, IP_TOS, tos) < 0) n = -1;
	}
# endif
# ifdef	SOL_SOCKET
#  ifdef	SO_KEEPALIVE
	if (opt & SCK_KEEPALIVE) {
		if (setsockopt2(s, SOL_SOCKET, SO_KEEPALIVE, 1) < 0) n = -1;
	}
#  endif
	if (opt & SCK_REUSEADDR) {
#  ifdef	SO_REUSEADDR
		if (setsockopt2(s, SOL_SOCKET, SO_REUSEADDR, 1) < 0) n = -1;
#  endif
#  ifdef	SO_REUSEPORT
		if (setsockopt2(s, SOL_SOCKET, SO_REUSEPORT, 1) < 0) n = -1;
#  endif
	}
# endif

	return(n);
}
