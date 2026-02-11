teco_get_inquiry_82 (Teco_Scanner * dev)
{
  CDB cdb;
  SANE_Status status;
  size_t size;

  DBG (DBG_proc, "teco_get_inquiry_82: enter\n");

  size = 0x4;
  MKSCSI_INQUIRY (cdb, size);
  cdb.data[1] = 1;
  cdb.data[2] = 0x82;

  status = sanei_scsi_cmd2 (dev->sfd, cdb.data, cdb.len,
			    NULL, 0, dev->buffer, &size);

  if (status)
    {
      DBG (DBG_error,
	   "teco_get_inquiry_82: inquiry page 0x82 failed with status %s\n",
	   sane_strstatus (status));
      return (SANE_FALSE);
    }

  size = dev->buffer[3] + 4;
  MKSCSI_INQUIRY (cdb, size);
  cdb.data[1] = 1;
  cdb.data[2] = 0x82;

  status = sanei_scsi_cmd2 (dev->sfd, cdb.data, cdb.len,
			    NULL, 0, dev->buffer, &size);

  if (status)
    {
      DBG (DBG_error,
	   "teco_get_inquiry_82: inquiry page 0x82 failed with status %s\n",
	   sane_strstatus (status));
      return (SANE_FALSE);
    }

  hexdump (DBG_info2, "inquiry page 0x82", dev->buffer, size);

  DBG (DBG_proc, "teco_get_inquiry_82: leave\n");

  return (status);
}
