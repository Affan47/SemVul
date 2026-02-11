InitPVars(RTree_t * rtp)
{
    register int i;

    rtp->split.Partitions[0].count[0] = rtp->split.Partitions[0].count[1] =
	0;
    rtp->split.Partitions[0].cover[0] = rtp->split.Partitions[0].cover[1] =
	NullRect();
    rtp->split.Partitions[0].area[0] = rtp->split.Partitions[0].area[1] =
	0;
    for (i = 0; i < NODECARD + 1; i++) {
	rtp->split.Partitions[0].taken[i] = FALSE;
	rtp->split.Partitions[0].partition[i] = -1;
    }
}
