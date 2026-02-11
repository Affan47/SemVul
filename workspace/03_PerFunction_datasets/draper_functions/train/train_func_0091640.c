lam_osd_blkadv(MPI_Win win)
{
	int		err;


	if (win->w_req->rq_state == LAM_RQSINIT) {
		if ((err = _mpi_req_start(win->w_req)) != MPI_SUCCESS) {
			return(err);
		}

		_mpi_req_blkset_m(win->w_req);
	}

	return(_mpi_req_advance());
}
