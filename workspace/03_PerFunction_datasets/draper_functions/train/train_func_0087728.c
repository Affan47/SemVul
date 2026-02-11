gmm_valid_input(Recog *recog)
{
  if (recog->gc->max_d == NULL) return FALSE;
  if (recog->gc->is_voice[recog->gc->max_i]) {
    return TRUE;
  }
  return FALSE;
}
