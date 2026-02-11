ipmi_get_sensor_type_string (uint8_t sensor_type)
{
  if (IPMI_SENSOR_TYPE_VALID (sensor_type))
    return (ipmi_sensor_types[sensor_type]);

  if (IPMI_SENSOR_TYPE_IS_OEM (sensor_type))
    return (ipmi_oem_sensor_type);

  return (NULL);
}
