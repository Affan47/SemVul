umax_set_lamp_status(SANE_Handle handle, int lamp_on)
{
 Umax_Scanner *scanner = handle;
 int lamp_status;
 SANE_Status status;

  DBG(DBG_proc, "umax_set_lamp_status\n");

  if (umax_scsi_open(scanner->device->sane.name, scanner->device, sense_handler,
                     scanner->device) != SANE_STATUS_GOOD )
  {
     DBG(DBG_error, "ERROR: umax_set_lamp_status: open of %s failed:\n", scanner->device->sane.name);
     return SANE_STATUS_INVAL;
  }

  status = umax_scsi_get_lamp_status(scanner->device, &lamp_status);

  if (!status)
  {
    status = umax_scsi_set_lamp_status(scanner->device, lamp_on);
  }

  umax_scsi_close(scanner->device);

 return status;
}
