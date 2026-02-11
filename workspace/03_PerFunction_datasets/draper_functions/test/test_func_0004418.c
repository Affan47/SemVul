process_restart (j_decompress_ptr cinfo)
{
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  int ci;


  cinfo->marker->discarded_bytes += entropy->bitstate.bits_left / 8;
  entropy->bitstate.bits_left = 0;


  if (! (*cinfo->marker->read_restart_marker) (cinfo))
    return FALSE;


  for (ci = 0; ci < cinfo->comps_in_scan; ci++)
    entropy->saved.last_dc_val[ci] = 0;

  entropy->saved.EOBRUN = 0;


  entropy->restarts_to_go = cinfo->restart_interval;


  if (cinfo->unread_marker == 0)
    entropy->pub.insufficient_data = FALSE;

  return TRUE;
}
