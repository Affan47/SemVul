scanning_frame(Microtek_Scanner *ms)
{
  uint8_t *data, comm[15] = { 0x04, 0, 0, 0, 0x09, 0 };
  int x1, y1, x2, y2;

  DBG(23, ".scanning_frame...\n");

  x1 = ms->x1;
  x2 = ms->x2;
  y1 = ms->y1;
  y2 = ms->y2;

  if (ms->unit_type == MS_UNIT_18INCH) {
    x1 /= 2;
    x2 /= 2;
    y1 /= 2;
    y2 /= 2;
  }

  DBG(23, ".scanning_frame:  in- %d,%d  %d,%d\n",
      ms->x1, ms->y1, ms->x2, ms->y2);
  DBG(23, ".scanning_frame: out- %d,%d  %d,%d\n", x1, y1, x2, y2);
  data = comm + 6;
  data[0] =
    ((ms->unit_type == MS_UNIT_PIXELS) ? 0x08 : 0 ) |
    ((ms->mode == MS_MODE_HALFTONE) ? 0x01 : 0 );
  data[1] = x1 & 0xFF;
  data[2] = (x1 >> 8) & 0xFF;
  data[3] = y1 & 0xFF;
  data[4] = (y1 >> 8) & 0xFF;
  data[5] = x2 & 0xFF;
  data[6] = (x2 >> 8) & 0xFF;
  data[7] = y2 & 0xFF;
  data[8] = (y2 >> 8) & 0xFF;
  if (DBG_LEVEL >= 192) {
    int i;
#if 0
    fprintf(stderr, "SF: ");
    for (i=0;i<6+0x09;i++) fprintf(stderr, "%2x ", comm[i]);
    fprintf(stderr, "\n");
#endif
    MDBG_INIT("SF: ");
    for (i=0;i<6+0x09;i++) MDBG_ADD("%2x ", comm[i]);
    MDBG_FINISH(192);
  }
  return sanei_scsi_cmd(ms->sfd, comm, 6 + 0x09, 0, 0);
}
