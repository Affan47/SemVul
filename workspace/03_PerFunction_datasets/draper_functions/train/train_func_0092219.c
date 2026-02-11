fsckwsphdr()
{
	struct fsck_blk_map_hdr fsckwsp;

	if (get_fsckwsphdr(&fsckwsp)) {
		fputs("fsckwsphdr: error returned from get_fsckwsphdr()\n\n", stderr);
		return;
	}
	if (display_fsck_wsphdr(&fsckwsp) == XPEEK_CHANGED)
		if (put_fsckwsphdr(&fsckwsp))
			fputs("fsckwsphdr: error returned from put_fsckwsphdr()\n\n", stderr);
	return;
}
