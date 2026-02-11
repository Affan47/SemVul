index_close_fds(index_t* ind) {
	kdtree_fits_t* io;
	if (ind->quads->fb->fid) {
		if (fclose(ind->quads->fb->fid)) {
			SYSERROR("Failed to fclose() an astrometry_net_data quadfile");
			return -1;
		}
		ind->quads->fb->fid = NULL;
	}
	io = ind->codekd->tree->io;
	if (io->fid) {
		if (fclose(io->fid)) {
			SYSERROR("Failed to fclose() an astrometry_net_data code kdtree");
			return -1;
		}
		io->fid = NULL;
	}
	io = (kdtree_fits_t*)ind->starkd->tree->io;
	if (io->fid) {
		if (fclose(io->fid)) {
			SYSERROR("Failed to fclose() an astrometry_net_data star kdtree");
			return -1;
		}
		io->fid = NULL;
	}
	return 0;
}
