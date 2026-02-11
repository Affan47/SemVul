_get_track_green_cdrdao(void *user_data, track_t i_track)
{
  _img_private_t *env = user_data;

  if (!env->gen.init) _init_cdrdao(env);

  if (i_track > env->gen.i_tracks || i_track == 0)
    return false;

  return env->tocent[i_track-env->gen.i_first_track].track_green;
}
