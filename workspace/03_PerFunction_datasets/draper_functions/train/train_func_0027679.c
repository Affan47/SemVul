__destroy_ii(ii *i)
{

	if(i->song) mpd_freeSong(i->song);

	if(i->uris)
	{
		g_list_foreach(i->uris, (GFunc)meta_data_free, NULL);
		g_list_free(i->uris);
	}
	if(i->releases)
	{
		g_list_foreach(i->releases,(GFunc) g_free, NULL);
		g_list_free(i->releases);
	}
	g_slice_free(ii, i);
}
