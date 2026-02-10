gl841_set_buffer_address_gamma (Genesys_Device * dev, uint32_t addr)
{
  SANE_Status status;

  DBG (DBG_io, "gl841_set_buffer_address_gamma: setting address to 0x%05x\n",
       addr & 0xfffffff0);

  addr = addr >> 4;

  status = sanei_genesys_write_register (dev, 0x5c, (addr & 0xff));
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_set_buffer_address_gamma: failed while writing low byte: %s\n",
	   sane_strstatus (status));
      return status;
    }

  addr = addr >> 8;
  status = sanei_genesys_write_register (dev, 0x5b, (addr & 0xff));
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_set_buffer_address_gamma: failed while writing high byte: %s\n",
	   sane_strstatus (status));
      return status;
    }

  DBG (DBG_io, "gl841_set_buffer_address_gamma: completed\n");

  return status;
}
