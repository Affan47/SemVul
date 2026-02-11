sanei_genesys_set_buffer_address (Genesys_Device * dev, uint32_t addr)
{
  SANE_Status status;

  if(dev->model->asic_type==GENESYS_GL847
  || dev->model->asic_type==GENESYS_GL845
  || dev->model->asic_type==GENESYS_GL846
  || dev->model->asic_type==GENESYS_GL124)
    {
      DBG (DBG_warn,
	   "sanei_genesys_set_buffer_address: shouldn't be used for GL846+ ASICs\n");
      return SANE_STATUS_GOOD;
    }

  DBG (DBG_io,
       "sanei_genesys_set_buffer_address: setting address to 0x%05x\n",
       addr & 0xfffffff0);

  addr = addr >> 4;

  status = sanei_genesys_write_register (dev, 0x2b, (addr & 0xff));
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "sanei_genesys_set_buffer_address: failed while writing low byte: %s\n",
	   sane_strstatus (status));
      return status;
    }

  addr = addr >> 8;
  status = sanei_genesys_write_register (dev, 0x2a, (addr & 0xff));
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "sanei_genesys_set_buffer_address: failed while writing high byte: %s\n",
	   sane_strstatus (status));
      return status;
    }

  DBG (DBG_io, "sanei_genesys_set_buffer_address: completed\n");

  return status;
}
