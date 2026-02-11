set_dc_offset_to_zero()
{
  int i;

  if(!signalcomps)
  {
    return;
  }

  for(i=0; i<signalcomps; i++)
  {
    signalcomp[i]->screen_offset = 0.0;
  }

  maincurve->drawCurve_stage_1();
}
