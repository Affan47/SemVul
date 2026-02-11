player_launch (const char *title, const char *mrl,
		    int pos, int pos_time, int duration)
{
  int err;
  pthread_attr_t attr;

  goto_pos  = pos < 0 ? 0 : pos;
  goto_time = pos_time < 0 ? 0 : pos_time;
  end_time = duration <= 0 ? 0: pos_time + duration;
  free (cur_title);
  free (cur_mrl);
  cur_title = title && !playlist_showing_logo () ? strdup (title) : NULL;
  cur_mrl = strdup (mrl);

  gtk_video_unblank_screen ((GtkVideo *)gtv);

  if (!demuxer_for_logo && playlist_showing_logo ())
    return;


  pthread_attr_init (&attr);
  pthread_attr_setstacksize (&attr, 256 * 1024);
  if ((err = pthread_create (&play_thread, &attr, play_exec, NULL)) != 0)
  {
    display_error_modal (FROM_GXINE, _("Player failure"),
			 _("Can't create new thread: %s\n"), strerror(err));
    abort();
  }

  if (!playlist_showing_logo ())
    pthread_detach (play_thread);

  pthread_attr_destroy (&attr);
}
