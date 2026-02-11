s_connect(int sockfd,
		     const struct sockaddr *addr,
		     size_t addr_s,
		     time_t connect_timeout)
{
	fd_set fdr;
	struct timeval tv;
	int	rc;

#ifdef SOL_KEEPALIVE
	setsockopt(sockfd, SOL_SOCKET, SOL_KEEPALIVE,
		   (const char *)&dummy, sizeof(dummy));
#endif

#ifdef  SOL_LINGER
        {
		struct linger l;

                l.l_onoff=0;
                l.l_linger=0;

                setsockopt(sockfd, SOL_SOCKET, SOL_LINGER,
			   (const char *)&l, sizeof(l));
        }
#endif


        if (connect_timeout == 0)
                return ( connect(sockfd, addr, addr_s));


        if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)     return (-1);

        if ( connect(sockfd, addr, addr_s) == 0)
        {


                if (fcntl(sockfd, F_SETFL, 0) < 0)      return (-1);
                return (0);
        }

	if (errno != EINPROGRESS)
		return -1;


        FD_ZERO(&fdr);
        FD_SET(sockfd, &fdr);
        tv.tv_sec=connect_timeout;
        tv.tv_usec=0;

        rc=select(sockfd+1, 0, &fdr, 0, &tv);
        if (rc < 0)     return (-1);

        if (!FD_ISSET(sockfd, &fdr))
        {
                errno=ETIMEDOUT;
                return (-1);
        }

	{
		int     gserr;
		socklen_t gslen = sizeof(gserr);

		if (getsockopt(sockfd, SOL_SOCKET,
			       SO_ERROR,
			       (char *)&gserr, &gslen)==0)
		{
			if (gserr == 0)
				return 0;

			errno=gserr;
		}
	}
	return (-1);
}
