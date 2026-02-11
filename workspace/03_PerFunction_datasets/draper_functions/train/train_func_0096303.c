sanei_genesys_init_structs (Genesys_Device * dev)
{
  unsigned int i, sensor_ok = 0, gpo_ok = 0, motor_ok = 0;


  for (i = 0; i < sizeof (Sensor) / sizeof (Genesys_Sensor); i++)
    {
      if (dev->model->ccd_type == Sensor[i].sensor_id)
	{
	  memcpy (&dev->sensor, &Sensor[i], sizeof (Genesys_Sensor));
	  sensor_ok = 1;
	}
    }


  for (i = 0; i < sizeof (Gpo) / sizeof (Genesys_Gpo); i++)
    {
      if (dev->model->gpo_type == Gpo[i].gpo_id)
	{
	  memcpy (&dev->gpo, &Gpo[i], sizeof (Genesys_Gpo));
	  gpo_ok = 1;
	}
    }


  for (i = 0; i < sizeof (Motor) / sizeof (Genesys_Motor); i++)
    {
      if (dev->model->motor_type == Motor[i].motor_id)
	{
	  memcpy (&dev->motor, &Motor[i], sizeof (Genesys_Motor));
	  motor_ok = 1;
	}
    }


  if (sensor_ok == 0 || motor_ok == 0 || gpo_ok == 0)
    {
      DBG (DBG_error0,
	   "sanei_genesys_init_structs: bad description(s) for ccd/gpo/motor=%d/%d/%d\n",
	   dev->model->ccd_type, dev->model->gpo_type,
	   dev->model->motor_type);
    }


  dev->ld_shift_r = dev->model->ld_shift_r;
  dev->ld_shift_g = dev->model->ld_shift_g;
  dev->ld_shift_b = dev->model->ld_shift_b;
}
