sanei_lexmark_low_assign_sensor (Lexmark_Device * dev)
{
  int dn;


  dn = 0;
  while (sensor_list[dn].id != 0
	 && sensor_list[dn].id != dev->model.sensor_type)
    dn++;
  if (sensor_list[dn].id == 0)
    {
      DBG (1,
	   "sanei_lexmark_low_assign_sensor: unknown sensor %d\n",
	   dev->model.sensor_type);
      return SANE_STATUS_UNSUPPORTED;
    }
  dev->sensor = &(sensor_list[dn]);
  DBG (1, "sanei_lexmark_low_assign_sensor: assigned sensor number %d\n",
       dev->model.sensor_type);
  return SANE_STATUS_GOOD;
}
