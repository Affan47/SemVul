sanei_genesys_exposure_time (Genesys_Device * dev, Genesys_Register_Set * reg,
			     int xdpi)
{
  if (dev->model->motor_type == MOTOR_5345)
    {
      if (dev->model->cmd_set->get_filter_bit (reg))
	{

	  switch (xdpi)
	    {
	    case 600:
	      return 8500;
	    case 500:
	    case 400:
	    case 300:
	    case 250:
	    case 200:
	    case 150:
	      return 5500;
	    case 100:
	      return 6500;
	    case 50:
	      return 12000;
	    default:
	      return 11000;
	    }
	}
      else
	{

	  switch (xdpi)
	    {
	    case 300:
	    case 250:
	    case 200:
	      return 5500;
	    case 50:
	      return 12000;
	    default:
	      return 11000;
	    }
	}
    }
  else if (dev->model->motor_type == MOTOR_HP2400)
    {
      if (dev->model->cmd_set->get_filter_bit (reg))
	{

	  switch (xdpi)
	    {
	    case 200:
	      return 7210;
	    default:
	      return 11111;
	    }
	}
      else
	{

	  switch (xdpi)
	    {
	    case 600:
	      return 8751;
	    default:
	      return 11111;
	    }
	}
    }
  else if (dev->model->motor_type == MOTOR_HP2300)
    {
      if (dev->model->cmd_set->get_filter_bit (reg))
	{

	  switch (xdpi)
	    {
	    case 600:
	      return 8699;
	    case 300:
	      return 3200;
	    case 150:
	      return 4480;
	    case 75:
	      return 5500;
	    default:
	      return 11111;
	    }
	}
      else
	{

	  switch (xdpi)
	    {
	    case 600:
	      return 8699;
	    case 300:
	      return 4349;
	    case 150:
	    case 75:
	      return 4480;
	    default:
	      return 11111;
	    }
	}
    }
  return dev->settings.exposure_time;
}
