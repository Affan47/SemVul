p_framenr_from_go_number(GapPlayerMainGlobalParams *gpp, gint32 go_number)
{


  if((gpp->go_base_framenr < 0) || (gpp->go_base < 0))
  {
    gpp->go_base_framenr = gpp->play_current_framenr;
    gpp->go_base = go_number;
  }


  return CLAMP(gpp->go_base_framenr  + (go_number - gpp->go_base)
                     , gpp->ainfo_ptr->first_frame_nr
                     , gpp->ainfo_ptr->last_frame_nr
                     );
}
