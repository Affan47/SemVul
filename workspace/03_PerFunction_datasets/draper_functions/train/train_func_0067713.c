track_disp_hdr_cb(const route_head* track)
{
  cur_info = &route_info[route_idx];
  cur_info->prev_wpt = NULL;
  cur_info->total = 0;
  current_trk = (route_head*)track;
  if (track->rte_waypt_ct <= 0) {
    return;
  }

  if (!gtxt_flags.track_header_written) {
    gtxt_flags.track_header_written = 1;
    gbfprintf(fout, "\r\n\r\nHeader\t%s\r\n", headers[track_header]);
  }

  print_string("\r\nTrack\t%s\t", current_trk->rte_name ? current_trk->rte_name : "");
  print_date_and_time(cur_info->start, 0);
  print_date_and_time(cur_info->time, 1);
  print_distance(cur_info->length, 0, 1, 0);
  print_speed(&cur_info->length, &cur_info->time);
  print_string("%s", (track->rte_url != NULL) ? track->rte_url : "");
  gbfprintf(fout, "\r\n\r\nHeader\t%s\r\n\r\n", headers[trkpt_header]);
}
