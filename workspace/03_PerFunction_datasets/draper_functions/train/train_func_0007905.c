p_story_local_wanted_framenr(GapStoryLocateRet *ret_elem, GapStoryElem *stb_elem, gint32 wanted_framenr)
{
  gint32  l_rangesize;
  gdouble fnr;

  if(wanted_framenr > stb_elem->nframes)
  {
    printf("INTERNAL ERROR: p_story_local_wanted_framenr wanted_framenr:%d overflow (limit:%d)\n"
          ,(int)wanted_framenr
          ,(int)stb_elem->nframes
          );
    return;
  }

  l_rangesize = p_calculate_rangesize(stb_elem);


  if (stb_elem->to_frame >= stb_elem->from_frame)
  {

    if (stb_elem->playmode == GAP_STB_PM_PINGPONG)
    {
      ret_elem->ret_framenr = p_calculate_pingpong_framenr(wanted_framenr
                                                          ,l_rangesize
                                                          ,stb_elem->step_density
                                                          );
    }
    else
    {
      fnr = (gdouble)((wanted_framenr -1) % l_rangesize) * stb_elem->step_density;
      ret_elem->ret_framenr = 1 + (gint32)fnr;
    }
    ret_elem->ret_framenr += (stb_elem->from_frame -1);
  }
  else
  {

    if (stb_elem->playmode == GAP_STB_PM_PINGPONG)
    {
      ret_elem->ret_framenr = 1 + l_rangesize - p_calculate_pingpong_framenr(wanted_framenr
                                                                            ,l_rangesize
                                                                            ,stb_elem->step_density
                                                                            );
    }
    else
    {
      fnr = (gdouble)((l_rangesize - wanted_framenr) % l_rangesize) * stb_elem->step_density;
      ret_elem->ret_framenr = 1 + (gint32)fnr;
    }
    ret_elem->ret_framenr += (stb_elem->to_frame -1);
  }
  ret_elem->locate_ok = TRUE;
  ret_elem->stb_elem = stb_elem;

}
