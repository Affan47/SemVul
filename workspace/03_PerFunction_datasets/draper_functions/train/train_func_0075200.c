cd_advance(int cd_desc, struct disc_timeval time)
{
  struct disc_info disc;

  if(cd_stat(cd_desc, &disc) < 0)
    return -1;

  if(__internal_cd_track_advance(cd_desc, disc,
				 disc.disc_total_tracks, time) < 0)
    return -1;

  return 0;
}
