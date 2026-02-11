lam_bufdetach(void *pbuf, int *psize)
{
	int		err;
	struct _bsndhdr	*p;


	while (buftop) {


		_mpi_req_blkclr();

		for (p = buftop; p; p = p->bsh_next) {
			_mpi_req_blkset(p->bsh_req);
		}

		err = _mpi_req_advance();
		if (err != MPI_SUCCESS) return(err);
	}


	*((void **) pbuf) = userbuf;
	*psize = bufsize;

	userbuf = 0;
	bufsize = 0;
	buftop = bufend = buffree = 0;

	return(MPI_SUCCESS);
}
