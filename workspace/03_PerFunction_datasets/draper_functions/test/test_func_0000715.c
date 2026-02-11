low_get_start_loc (SANE_Int resolution, SANE_Int * vert_start,
		   SANE_Int * hor_start, SANE_Int offset,
		   Lexmark_Device * dev)
{
  SANE_Int start_600;

  switch (dev->model.sensor_type)
    {
    case X1100_2C_SENSOR:
    case X1200_USB2_SENSOR:
    case A920_SENSOR:
    case X1200_SENSOR:
      start_600 = 195 - offset;
      *hor_start = 0x68;
      break;
    case X1100_B2_SENSOR:
      start_600 = 195 - offset;
      switch (resolution)
	{
	case 75:
	  *hor_start = 0x68;
	  break;
	case 150:
	  *hor_start = 0x68;
	  break;
	case 300:
	  *hor_start = 0x6a;
	  break;
	case 600:
	  *hor_start = 0x6b;
	  break;
	case 1200:
	  *hor_start = 0x6b;
	  break;
	default:

	  return SANE_STATUS_INVAL;
	}
      break;
    case X74_SENSOR:
      start_600 = 268 - offset;
      switch (resolution)
	{
	case 75:
	  *hor_start = 0x48;
	  break;
	case 150:
	  *hor_start = 0x48;
	  break;
	case 300:
	  *hor_start = 0x4a;
	  break;
	case 600:
	  *hor_start = 0x4b;
	  break;
	default:

	  return SANE_STATUS_INVAL;
	}
      break;
    }

  switch (resolution)
    {
    case 75:
      *vert_start = start_600 / 8;
      break;
    case 150:
      *vert_start = start_600 / 4;
      break;
    case 300:
      *vert_start = start_600 / 2;
      break;
    case 600:
      *vert_start = start_600;
      break;
    case 1200:
      *vert_start = start_600 * 2;
      break;
    default:

      return SANE_STATUS_INVAL;
    }

  return SANE_STATUS_GOOD;
}
