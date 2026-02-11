io_init()))()

{
	int		i;
	int		fd;
	char		*iosname;


	if (lpattach("iod")) lampanic("iod (lpattach)");


	iosname = lam_get_iosockname();
	if (iosname == 0) lampanic("iod (killname)");

	if ((fd = sfh_sock_open_srv_unix_stm(iosname)) < 0) {
		lampanic("iod (sfh_sock_open_srv_unix_stm)");
	}

	free(iosname);

	if (fcntl(fd, F_SETFD, 1) == -1) {
	    lampanic("iod (fcntl)");
	}


	for (i = 0; i < FD_SETSIZE; i++) {
		fdmap[i].fe_node = NOTNODEID;
	}


	io_accept(fd);

	return(iod());
}
