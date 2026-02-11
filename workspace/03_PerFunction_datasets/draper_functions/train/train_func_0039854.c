write_control (Genesys_Device * dev, int resolution)
{
  SANE_Status status;
  uint8_t control[4];
  uint32_t addr = 0xdead;


  if (dev->model->motor_type == MOTOR_HP2300)
    return SANE_STATUS_GOOD;


  switch (dev->sensor.optical_res)
    {
    case 600:
      addr = 0x08200;
      break;
    case 1200:
      addr = 0x10200;
      break;
    case 2400:
      addr = 0x1fa00;
      break;
    default:
      DBG (DBG_error, "write_control: failed to compute control address\n");
      return SANE_STATUS_INVAL;
    }


  switch (dev->model->motor_type)
    {
    case MOTOR_XP200:

      control[0] = LOBYTE (resolution);
      control[1] = HIBYTE (resolution);
      control[2] = dev->control[4];
      control[3] = dev->control[5];
      break;
    case MOTOR_HP3670:
    case MOTOR_HP2400:
    case MOTOR_5345:
    default:
      control[0] = dev->control[2];
      control[1] = dev->control[3];
      control[2] = dev->control[4];
      control[3] = dev->control[5];
      break;
    }

  DBG (DBG_info,
       "write_control: control write=0x%02x 0x%02x 0x%02x 0x%02x\n",
       control[0], control[1], control[2], control[3]);
  status = sanei_genesys_set_buffer_address (dev, addr);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error, "write_control: failed to set up control address\n");
      return SANE_STATUS_INVAL;
    }
  status = gl646_bulk_write_data (dev, 0x3c, control, 4);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error, "write_control: failed to set up control\n");
      return SANE_STATUS_INVAL;
    }
  return status;
}
