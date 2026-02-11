find_rgns (void)
{
  if (sel_sched_p () && flag_sel_sched_pipelining)
    sel_find_rgns ();
  else
    haifa_find_rgns ();
}
