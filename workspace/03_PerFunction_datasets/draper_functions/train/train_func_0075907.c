send_join_response(int fd, LaneControl_t *lc, int lecid,
		   unsigned int status)
{
  Debug_unit(&conn_unit,"Send_join_response called to %d",fd);
  lc->opcode = htons(LE_JOIN_RESPONSE);
  lc->status = (unsigned short)htons(0xffff & status);
  lc->lecid = lecid;

  if (send_control_frame(fd, lc) == 0) {
    dump_error(&conn_unit,"Send join response failed");
    return 0;
  }
  return 1;
}
