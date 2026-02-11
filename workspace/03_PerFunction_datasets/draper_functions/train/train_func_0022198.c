reconstruct_sounds(state_t *s)
{
  song_t *seeker;
  int it_type = s->resmgr->sci_version >= SCI_VERSION_01 ?
    SCI_SONG_ITERATOR_TYPE_SCI1
    : SCI_SONG_ITERATOR_TYPE_SCI0;

  if (s->sound.songlib.lib)
    seeker = *(s->sound.songlib.lib);
  else
    {
      song_lib_init(&s->sound.songlib);
      seeker = NULL;
    }
  while (seeker)
    {
      song_iterator_t *base, *ff;
      int oldstatus;
      song_iterator_message_t msg;

      base = ff = build_iterator(s, seeker->resource_num, it_type, seeker->handle);
      if (seeker->restore_behavior == RESTORE_BEHAVIOR_CONTINUE)
	  ff = (song_iterator_t *) new_fast_forward_iterator(base, seeker->restore_time);
      ff->init(ff);

      msg = songit_make_message(seeker->handle, SIMSG_SET_LOOPS(seeker->loops));
      songit_handle_message(&ff, msg);
      msg = songit_make_message(seeker->handle, SIMSG_SET_HOLD(seeker->hold));
      songit_handle_message(&ff, msg);


      oldstatus = seeker->status;
      seeker->status = SOUND_STATUS_STOPPED;
      seeker->it = ff;
      sfx_song_set_status(&s->sound, seeker->handle, oldstatus);
      seeker = seeker->next;
    }

}
