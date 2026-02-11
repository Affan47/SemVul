flush_all_buffered_windows()
{
  int i;

  for (i=0; i<nof_active_z_windows; i++)
    if (bool_equal(z_windows[i]->buffering, true))
      wordwrap_flush_output(z_windows[i]->wordwrapper);
}
