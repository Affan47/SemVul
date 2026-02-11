uninit_sound_track_list (void)
{
  dmsg (D_MISC, "free sound track hash");
  hash_free (st_hash);
  XFREE0 (st_array);
  n_st = 0;
}
