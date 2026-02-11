low_cancel (SANE_Int devnum)
{
  SANE_Status status;

  DBG (2, "low_cancel: start\n");
  status = low_stop_mvmt (devnum);
  if (status != SANE_STATUS_GOOD)
    return status;
  status = low_clr_c6 (devnum);
  if (status != SANE_STATUS_GOOD)
    return status;
  DBG (2, "low_cancel: end.\n");
  return status;
}
