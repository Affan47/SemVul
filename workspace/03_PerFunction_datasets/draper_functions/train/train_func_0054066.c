send_tune_scan_length (Avision_Scanner* s)
{
  int top, bottom;

  SANE_Status status;
  size_t size;
  struct command_send scmd;
  struct truncate_attach {
    uint8_t vertical [2];

  } payload;

  DBG (3, "send_tune_scan_length:\n");

  memset (&scmd, 0, sizeof (scmd));

  size = sizeof (payload);
  scmd.opc = AVISION_SCSI_SEND;
  scmd.datatypecode = 0x96;
  set_triple (scmd.transferlen, size);


  top = 1200 * SANE_UNFIX (s->val[OPT_OVERSCAN_TOP].w) / MM_PER_INCH;
  DBG (3, "send_tune_scan_length: top: %d\n", top);

  set_double (scmd.datatypequal, 0x0001);
  set_double (payload.vertical, top);


  status = avision_cmd (&s->av_con, &scmd, sizeof (scmd),
			&payload, sizeof (payload), 0, 0);

  if (status != SANE_STATUS_GOOD) {
    DBG (1, "send_tune_scan_length: send top/left failed (%s)\n", sane_strstatus (status));
    return status;
  }

  scmd.datatypecode = 0x95;
  bottom = 1200 * SANE_UNFIX (s->val[OPT_OVERSCAN_BOTTOM].w) / MM_PER_INCH;
  DBG (3, "send_tune_scan_length: bottom: %d\n", bottom);

  set_double (payload.vertical, bottom);


  size = sizeof (payload);
  status = avision_cmd (&s->av_con, &scmd, sizeof (scmd),
			&payload, sizeof (payload), 0, 0);

  if (status != SANE_STATUS_GOOD) {
    DBG (1, "send_tune_scan_length: send bottom/right failed (%s)\n", sane_strstatus (status));
    return status;
  }

  return SANE_STATUS_GOOD;
}
