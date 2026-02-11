tilemap_set_transmask( struct tilemap *tilemap, int which, UINT32 fgmask, UINT32 bgmask )
{
	if( tilemap->fgmask[which] != fgmask || tilemap->bgmask[which] != bgmask )
	{
		tilemap->fgmask[which] = fgmask;
		tilemap->bgmask[which] = bgmask;
		tilemap_mark_all_tiles_dirty( tilemap );
	}
}
