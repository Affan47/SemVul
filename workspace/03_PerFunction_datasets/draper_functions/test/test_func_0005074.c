unity_webapps_music_player_context_playlist_activated (UnityMusicPlayer *player,
						       gchar *playlist_id,
						       gpointer user_data)
{
  UnityWebappsMusicPlayerContext *context;
  const gchar *playlist_name;

  context = (UnityWebappsMusicPlayerContext *)user_data;
  playlist_name = (const gchar *)g_hash_table_lookup (context->playlist_names_by_id, playlist_id);
  if (playlist_name == NULL)
    {
      UNITY_WEBAPPS_NOTE (MUSIC_PLAYER, "Got playlist activation for playlist we don't know about");
    }

  emit_playlist_activated_signal (context, playlist_name);
}
