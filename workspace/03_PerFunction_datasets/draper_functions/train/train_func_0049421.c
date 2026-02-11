umax_do_request_sense(Umax_Device *dev)
{
 size_t size = rs_return_block_size;
 SANE_Status status;

  DBG(DBG_proc, "do_request_sense\n");
  set_RS_allocation_length(request_sense.cmd, rs_return_block_size);
  status = umax_scsi_cmd(dev, request_sense.cmd, request_sense.size, dev->buffer[0], &size);
  if (status)
  {
    DBG(DBG_error, "umax_do_request_sense: command returned status %s\n", sane_strstatus(status));
  }
}
