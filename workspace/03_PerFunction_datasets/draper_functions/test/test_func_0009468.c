process_pmgr_gather (mvapich_state_t *st, int *rootp,
		int *sizep, void **bufp, int rank)
{
	if (recv_common_value (st, rootp, rank) < 0)
		return (-1);
	if (recv_common_value (st, sizep, rank) < 0)
		return (-1);
	if (*bufp == NULL)
		*bufp = xmalloc (*sizep * st->nprocs);

	mvapich_debug3 ("PMGR_GATHER: recv from rank %d", rank);
	if (mvapich_recv(st, (*bufp) + (*sizep)*rank, *sizep, rank) < 0) {
		error ("mvapich: PMGR_/GATHER: rank %d: recv: %m", rank);
		return (-1);
	}
	return (0);
}
