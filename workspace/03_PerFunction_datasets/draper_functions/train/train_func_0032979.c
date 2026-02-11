cdio_get_track_green(const CdIo_t *p_cdio, track_t i_track)
{
  if (p_cdio == NULL) {
    return false;
  }

  if (p_cdio->op.get_track_green) {
    return p_cdio->op.get_track_green (p_cdio->env, i_track);
  } else {
    return false;
  }
}
