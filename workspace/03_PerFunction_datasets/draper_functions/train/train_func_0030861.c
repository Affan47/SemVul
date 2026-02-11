extend_h_i_d (void)
{
  int reserve = (get_max_uid () + 1 - h_i_d.length ());
  if (reserve > 0
      && ! h_i_d.space (reserve))
    {
      h_i_d.safe_grow_cleared (3 * get_max_uid () / 2);
      sched_extend_target ();
    }
}
