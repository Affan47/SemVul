total_file_blocks(struct gfs2_sbd *sdp,
				      uint64_t filesize, int journaled)
{
	unsigned int data_blks = 0, meta_blks = 0;
	unsigned int max, height, bsize;
	uint64_t *arr;


	if (filesize <= sdp->bsize - sizeof(struct gfs2_dinode)) {
		goto out;
	}

	if (journaled) {
		arr = sdp->sd_jheightsize;
		max = sdp->sd_max_jheight;
		bsize = sdp->sd_jbsize;
	} else {
		arr = sdp->sd_heightsize;
		max = sdp->sd_max_height;
		bsize = sdp->bsize;
	}
	data_blks = DIV_RU(filesize, bsize);

	for (height = 0; height < max; height++)
		if (arr[height] >= filesize)
			break;
	if (height == 1) {
		goto out;
	}

	meta_blks = DIV_RU(data_blks, sdp->sd_inptrs);
out:
	return data_blks + meta_blks;
}
