can_unit_load(const struct unit *pcargo, const struct unit *ptrans)
{


  if (!same_pos(unit_tile(pcargo), unit_tile(ptrans))) {
    return FALSE;
  }

  return could_unit_load(pcargo, ptrans);
}
