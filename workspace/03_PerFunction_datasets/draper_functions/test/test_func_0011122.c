gl841_slow_back_home (Genesys_Device * dev, SANE_Bool wait_until_home)
{
  Genesys_Register_Set local_reg[GENESYS_GL841_MAX_REGS+1];
  SANE_Status status;
  uint8_t val;

  DBG (DBG_proc, "gl841_slow_back_home (wait_until_home = %d)\n",
       wait_until_home);

  if (dev->model->is_sheetfed == SANE_TRUE)
    {
      DBG (DBG_proc, "gl841_slow_back_home: there is no \"home\"-concept for sheet fed\n");
      DBG (DBG_proc, "gl841_slow_back_home: finished\n");
      return SANE_STATUS_GOOD;
    }

  memset (local_reg, 0, sizeof (local_reg));
  val = 0;
  status = sanei_genesys_get_status (dev, &val);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_slow_back_home: failed to read home sensor: %s\n",
	   sane_strstatus (status));
      return status;
    }

  dev->scanhead_position_in_steps = 0;

  if (val & REG41_HOMESNR)
    {
      DBG (DBG_info,
	   "gl841_slow_back_home: already at home, completed\n");
      dev->scanhead_position_in_steps = 0;
      return SANE_STATUS_GOOD;
    }

  status = gl841_stop_action (dev);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_slow_back_home: failed to stop motor: %s\n",
	   sane_strstatus (status));
      return SANE_STATUS_IO_ERROR;
    }

  memcpy (local_reg, dev->reg, (GENESYS_GL841_MAX_REGS+1) * sizeof (Genesys_Register_Set));

  gl841_init_optical_regs_off(local_reg);

  gl841_init_motor_regs(dev,local_reg,
			65536,MOTOR_ACTION_GO_HOME,0);

  status =
    gl841_bulk_write_register (dev, local_reg, GENESYS_GL841_MAX_REGS);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_slow_back_home: failed to bulk write registers: %s\n",
	   sane_strstatus (status));
      return status;
    }

  status = gl841_start_action (dev);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_slow_back_home: failed to start motor: %s\n",
	   sane_strstatus (status));
      gl841_stop_action (dev);

      gl841_bulk_write_register (dev, dev->reg, GENESYS_GL841_MAX_REGS);
      return status;
    }

  if (wait_until_home)
    {
      int loop = 0;

      while (loop < 300)
	{
	  status = sanei_genesys_get_status (dev, &val);
	  if (status != SANE_STATUS_GOOD)
	    {
	      DBG (DBG_error,
		   "gl841_slow_back_home: failed to read home sensor: %s\n",
		   sane_strstatus (status));
	      return status;
	    }

	  if (val & 0x08)
	    {
	      DBG (DBG_info,
		   "gl841_slow_back_home: reached home position\n");
	      DBG (DBG_proc, "gl841_slow_back_home: finished\n");
	      return SANE_STATUS_GOOD;
	    }
	  usleep (100000);
	  ++loop;
	}


      gl841_stop_action (dev);
      DBG (DBG_error,
	   "gl841_slow_back_home: timeout while waiting for scanhead to go home\n");
      return SANE_STATUS_IO_ERROR;
    }

  DBG (DBG_info, "gl841_slow_back_home: scanhead is still moving\n");
  DBG (DBG_proc, "gl841_slow_back_home: finished\n");
  return SANE_STATUS_GOOD;
}
