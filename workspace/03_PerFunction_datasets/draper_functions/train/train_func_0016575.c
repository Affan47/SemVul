destroy(But *but)  {
  Can  *can = but->iPacket;

  assert(MAGIC(but));
  assert(MAGIC(can));
  assert((can->win == NULL) || MAGIC(can->win));
  can->but = NULL;
  but->iPacket = NULL;
  if (can->win == NULL)  {
    MAGIC_UNSET(can);
    wms_free(can);
  } else
    butWin_destroy(can->win);
  return(0);
}
