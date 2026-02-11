mode_select_barcode_param3 (BH_Scanner *s)
{
  static struct {
    SANE_Byte cmd[6];
    struct mode_page_33 mp;
  } select_cmd;
  SANE_Status status;
  size_t len;

  DBG (3, "mode_select_barcode_param3 called\n");


  memset (&select_cmd, 0, sizeof (select_cmd));
  select_cmd.cmd[0] = BH_SCSI_MODE_SENSE;
  select_cmd.cmd[2] = BH_MODE_BARCODE_PARAM3_PAGE_CODE;
  select_cmd.cmd[4] = sizeof(select_cmd.mp);

  len = sizeof(select_cmd.mp);
  status = sanei_scsi_cmd (s->fd, &select_cmd.cmd, sizeof (select_cmd.cmd),
			   &select_cmd.mp, &len);

  if (status == SANE_STATUS_GOOD)
    {
      DBG(8, "mode_select_barcode_param3: sensed values: contrast:%d patchmode:%d\n",
	  (int) _2btol(select_cmd.mp.barcodecontrast),
	  (int) _2btol(select_cmd.mp.patchmode));

      memset (&select_cmd.cmd, 0, sizeof (select_cmd.cmd));
      select_cmd.cmd[0] = BH_SCSI_MODE_SELECT;
      select_cmd.cmd[1] = 0x10;
      select_cmd.cmd[4] = sizeof(select_cmd.mp);

      select_cmd.mp.modedatalen = 0x00;
      select_cmd.mp.mediumtype = 0x00;
      select_cmd.mp.devicespecificparam = 0x00;
      select_cmd.mp.blockdescriptorlen = 0x00;

      select_cmd.mp.pagecode = BH_MODE_BARCODE_PARAM3_PAGE_CODE;
      select_cmd.mp.paramlen = 0x06;


      if (_OPT_VAL_WORD(s, OPT_BARCODE_CONTRAST) != 0)
	{
	  _lto2b(_OPT_VAL_WORD(s, OPT_BARCODE_CONTRAST), select_cmd.mp.barcodecontrast);
	}
      if (_OPT_VAL_WORD(s, OPT_BARCODE_PATCHMODE) != 0)
	{
	  _lto2b(_OPT_VAL_WORD(s, OPT_BARCODE_PATCHMODE), select_cmd.mp.patchmode);
	}

      DBG(8, "mode_select_barcode_param3: param values: contrast:%d patchmode:%d\n",
	  (int) _OPT_VAL_WORD(s, OPT_BARCODE_CONTRAST),
	  (int) _OPT_VAL_WORD(s, OPT_BARCODE_PATCHMODE));

      DBG(8, "mode_select_barcode_param3: select values: contrast:%d patchmode:%d\n",
	  (int) _2btol(select_cmd.mp.barcodecontrast),
	  (int) _2btol(select_cmd.mp.patchmode));

      status = sanei_scsi_cmd (s->fd, &select_cmd, sizeof (select_cmd), 0, 0);
    }

  return status;
}
