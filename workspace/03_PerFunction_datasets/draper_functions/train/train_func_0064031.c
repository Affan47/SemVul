p_mix_audio(FILE *fp
           ,gint16 *bufferl
           ,gint16 *bufferr
           ,GapStoryRenderVidHandle *vidhand
           ,gdouble aud_total_sec
           ,gdouble *mix_scale
           )
{
  gint32 l_track;
  gint32 l_min_track;
  gint32 l_max_track;

  gdouble l_max_peak;
  gdouble l_peak_posl;
  gdouble l_peak_posr;
  gdouble l_peak_negl;
  gdouble l_peak_negr;
  gdouble l_mixl;
  gdouble l_mixr;
  gdouble l_sample_left;
  gdouble l_sample_right;
  gdouble l_master_scale;
  gint32  l_master_sample_idx;
  gint32  l_max_sample_idx;


  l_peak_posl = 0.0;
  l_peak_posr = 0.0;
  l_peak_negl = 0.0;
  l_peak_negr = 0.0;
  l_sample_left = 0.0;
  l_sample_right = 0.0;

  l_master_scale = vidhand->master_volume;

  if((fp) || (bufferl) || (bufferr))
  {
    l_master_scale = *mix_scale * vidhand->master_volume;
  }

  l_max_sample_idx = aud_total_sec * vidhand->master_samplerate;

  p_find_min_max_aud_tracknumbers(vidhand->aud_list, &l_min_track, &l_max_track);

  for(l_master_sample_idx = 0; l_master_sample_idx < l_max_sample_idx; l_master_sample_idx++)
  {
    l_mixl = 0.0;
    l_mixr = 0.0;

    *vidhand->progress = (gdouble)l_master_sample_idx / (gdouble)l_max_sample_idx;


    for(l_track=l_min_track; l_track <= l_max_track; l_track++)
    {
      p_get_audio_sample(vidhand
                        ,l_track
                        ,l_master_sample_idx
                        ,&l_sample_left
                        ,&l_sample_right
                        );
      l_mixl += l_sample_left;
      l_mixr += l_sample_right;
    }
    l_mixl *= l_master_scale;
    l_mixr *= l_master_scale;

    if(fp)
    {

       gap_audio_wav_write_gint16(fp, (gint16)l_mixl);
       gap_audio_wav_write_gint16(fp, (gint16)l_mixr);
    }

    if(bufferl)
    {
       bufferl[l_master_sample_idx] = l_mixl;
    }
    if(bufferr)
    {
       bufferr[l_master_sample_idx] = l_mixr;
    }


    l_peak_posl = MAX(l_mixl,l_peak_posl);
    l_peak_posr = MAX(l_mixr,l_peak_posr);
    l_peak_negl = MIN(l_mixl,l_peak_negl);
    l_peak_negr = MIN(l_mixr,l_peak_negr);
  }

  l_max_peak = MAX(l_peak_posl, l_peak_posr);
  l_max_peak = MAX(l_max_peak, (-1.0 * l_peak_negl));
  l_max_peak = MAX(l_max_peak, (-1.0 * l_peak_negr));

  if (l_max_peak <= 32767)
  {


    *mix_scale = 1.0;
  }
  else
  {


    *mix_scale = 32767 / l_max_peak;
  }

}
