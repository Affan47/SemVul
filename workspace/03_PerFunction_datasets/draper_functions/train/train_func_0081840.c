_get_track_green_bincue(void *p_user_data, track_t i_track)
{
  _img_private_t *p_env = p_user_data;

  if ( NULL == p_env ||
       ( i_track < p_env->gen.i_first_track
	 || i_track >= p_env->gen.i_tracks + p_env->gen.i_first_track ) )
    return false;

  return p_env->tocent[i_track-p_env->gen.i_first_track].track_green;
}
