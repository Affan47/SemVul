flytec_delete(flytec_t *flytec)
{
    if (flytec) {
	snp_delete(flytec->snp);
	if (flytec->trackv) {
	    track_t **track;
	    for (track = flytec->trackv; *track; ++track)
		track_delete(*track);
	    free(flytec->trackv);
	}
	if (close(flytec->fd) == -1)
	    DIE("close", errno);
	free(flytec->pilot_name);
	free(flytec);
    }
}
