check_confidence()
{
  int flag;


  deltstop = deltconf*pow(deltfirst/deltconf, ratio_beta);

  flag = 0;
  if (deltstop < update->ntimestep - fix_event->event_timestep) flag = 1;

  return flag;
}
