get_airlift_text(const struct unit_list *punits,
                             const struct city *pdest)
{
  static struct astring str = ASTRING_INIT;
  bool src = (pdest == NULL);
  enum texttype { AL_IMPOSSIBLE, AL_UNKNOWN, AL_FINITE, AL_INFINITE }
      best = AL_IMPOSSIBLE;
  int cur = 0, max = 0;

  unit_list_iterate(punits, punit) {
    enum texttype this = AL_IMPOSSIBLE;
    enum unit_airlift_result result;


    result = test_unit_can_airlift_to(client_player(), punit, pdest);

    switch(result) {
    case AR_NO_MOVES:
    case AR_WRONG_UNITTYPE:
    case AR_OCCUPIED:
    case AR_NOT_IN_CITY:
    case AR_BAD_SRC_CITY:
    case AR_BAD_DST_CITY:

      this = AL_IMPOSSIBLE;
      break;
    case AR_OK:
    case AR_OK_SRC_UNKNOWN:
    case AR_OK_DST_UNKNOWN:
    case AR_SRC_NO_FLIGHTS:
    case AR_DST_NO_FLIGHTS:


      {
        const struct city *pcity = src ? tile_city(unit_tile(punit)) : pdest;
        fc_assert_ret_val(pcity != NULL, fc_strdup("-"));
        if (!src && (game.info.airlifting_style & AIRLIFTING_UNLIMITED_DEST)) {


          this = AL_INFINITE;
        } else if (client_player() == city_owner(pcity)) {

          int this_cur = pcity->airlift, this_max = city_airlift_max(pcity);
          if (this_max <= 0) {

            this = AL_IMPOSSIBLE;
          } else {
            if (src
                && (game.info.airlifting_style & AIRLIFTING_UNLIMITED_SRC)) {

              this = AL_INFINITE;
            } else {

              this = AL_FINITE;


              if (best == AL_FINITE) {
                fc_assert(cur == this_cur && max == this_max);
              }
              cur = this_cur;
              max = this_max;
            }
          }
        } else {

          this = AL_UNKNOWN;
        }
      }
      break;
    }


    best = MAX(best, this);
  } unit_list_iterate_end;

  switch(best) {
  case AL_IMPOSSIBLE:
    return NULL;
  case AL_UNKNOWN:
    astr_set(&str, "?");
    break;
  case AL_FINITE:
    astr_set(&str, "%d/%d", cur, max);
    break;
  case AL_INFINITE:
    astr_set(&str, _("Yes"));
    break;
  }

  return astr_str(&str);
}
