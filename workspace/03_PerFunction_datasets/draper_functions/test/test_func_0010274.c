p_get_next_framenr_in_sequence(GapPlayerMainGlobalParams *gpp)
{
  gint32 framenr;
  framenr = p_get_next_framenr_in_sequence2(gpp);

  if((framenr < 0)
  || (gpp->play_backward)
  || (gpp->audio_resync > 0))
  {

    p_audio_stop(gpp);


    if(gpp->audio_resync > 0)
    {
      gpp->audio_resync--;
    }
  }
  else
  {


#ifdef TRY_AUTO_SYNC_AT_FAST_PLAYBACKSPEED


    if (gpp->audio_required_samplerate > GAP_PLAYER_MAIN_MAX_SAMPLERATE)
    {
      gint32 nframes;


      nframes = 8 * (1 + (gpp->speed / 5));
      if((framenr % nframes)  == 0)
      {
        printf("WARNING: Audiospeed cant follow up video speed nframes:%d\n", (int)nframes);
        p_audio_resync(gpp);
      }
    }
#endif
    p_audio_start_play(gpp);
  }
  return(framenr);
}
