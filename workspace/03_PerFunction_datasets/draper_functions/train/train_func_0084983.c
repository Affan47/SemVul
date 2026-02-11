totem_playlist_clear_with_g_mount (TotemPlaylist *playlist,
				   GMount *mount)
{
	g_return_if_fail (mount != NULL);

	totem_playlist_clear_with_compare (playlist,
					   (ClearComparisonFunc) totem_playlist_compare_with_mount,
					   mount);
}
