mps_routetrlr_w(gbfile* mps_file, int mps_ver, const route_head* rte)
{
  char		hdr[2];
  int			value = 0;

  hdr[0] = 1;

  if (rte->waypoint_list.next) {
    gbfwrite(&value, 4, 1, mps_file);
    gbfwrite(hdr, 1, 1, mps_file);
  }
}
