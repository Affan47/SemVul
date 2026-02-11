ok_pressed(But *but)  {
  AbutMsg  *msg;

  msg = but_packet(but);
  assert(MAGIC(msg));
  if (msg->layer == 0)
    butWin_destroy(msg->win);
  else
    abutMsg_destroy(but_packet(but), TRUE);
  return(0);
}
