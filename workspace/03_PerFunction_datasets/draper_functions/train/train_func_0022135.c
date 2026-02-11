xen_blkbk_free_caches(struct xen_blkif *blkif)
{

	if (!RB_EMPTY_ROOT(&blkif->persistent_gnts))
		free_persistent_gnts(blkif, &blkif->persistent_gnts,
			blkif->persistent_gnt_c);

	BUG_ON(!RB_EMPTY_ROOT(&blkif->persistent_gnts));
	blkif->persistent_gnt_c = 0;


	shrink_free_pagepool(blkif, 0 );
}
