rdbx_check(const rdbx_t *rdbx, int delta) {

  if (delta > 0) {
    return err_status_ok;
  } else if ((int)(bitvector_get_length(&rdbx->bitmask) - 1) + delta < 0) {

    return err_status_replay_old;
  } else if (bitvector_get_bit(&rdbx->bitmask,
			       (int)(bitvector_get_length(&rdbx->bitmask) - 1) + delta) == 1) {

    return err_status_replay_fail;
  }


  return err_status_ok;
}
