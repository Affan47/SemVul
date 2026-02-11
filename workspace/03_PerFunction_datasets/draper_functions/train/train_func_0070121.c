gbemol_utils_get_song_image (GbemolMpdSong* song)
{
	GdkPixbuf *img = NULL;

	if (gbemol_cfg_get_bool("cover_art", "file"))
		img = gbemol_utils_get_cover_image_from_file(song);


	if (!img && gbemol_cfg_get_bool("cover_art", "amazon"))
	{
		img = gbemol_utils_get_cover_image_from_amazon(song);
	}

	return img;
}
