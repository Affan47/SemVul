get_disc_last_lsn_cdrdao (void *p_user_data)
{
  _img_private_t *p_env = p_user_data;
  track_t i_leadout = p_env->gen.i_tracks;
  uint16_t i_blocksize  = p_env->tocent[i_leadout-1].blocksize;
  long i_size;

  if (p_env->tocent[i_leadout-1].sec_count) {
    i_size = p_env->tocent[i_leadout-1].sec_count;
  } else {
    i_size = cdio_stream_stat(p_env->tocent[i_leadout-1].data_source)
      - p_env->tocent[i_leadout-1].offset;
    if (check_track_is_blocksize_multiple(p_env->tocent[i_leadout-1].filename,
					  i_leadout-1, i_size, i_blocksize)) {
      i_size /= i_blocksize;
    } else {

      i_size = (i_size / i_blocksize) + 1;
    }
  }

  i_size += p_env->tocent[i_leadout-1].start_lba;
  i_size -= CDIO_PREGAP_SECTORS;

  return i_size;
}
