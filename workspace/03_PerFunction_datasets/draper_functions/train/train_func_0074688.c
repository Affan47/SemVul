track_waypt_pr(const waypoint* wpt)
{
  (*cur_tx_tracklist_entry)->lat = wpt->latitude;
  (*cur_tx_tracklist_entry)->lon = wpt->longitude;
  (*cur_tx_tracklist_entry)->alt = (wpt->altitude != unknown_alt) ? wpt->altitude : 1e25;
  (*cur_tx_tracklist_entry)->Time = wpt->creation_time;
  if (wpt->shortname) {
    strncpy((*cur_tx_tracklist_entry)->trk_ident, wpt->shortname, sizeof((*cur_tx_tracklist_entry)->trk_ident));
    (*cur_tx_tracklist_entry)->trk_ident[sizeof((*cur_tx_tracklist_entry)->trk_ident)-1] = 0;
  }
  (*cur_tx_tracklist_entry)->tnew = wpt->wpt_flags.new_trkseg;
  cur_tx_tracklist_entry++;
}
