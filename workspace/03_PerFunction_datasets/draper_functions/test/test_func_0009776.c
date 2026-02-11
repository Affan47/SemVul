ipmi_get_oem_event_bitmask_message (uint32_t manufacturer_id,
                                    uint16_t product_id,
                                    uint8_t event_reading_type_code,
                                    uint8_t sensor_type,
                                    uint16_t event_bitmask,
                                    char *buf,
                                    unsigned int buflen)
{
  if (!buf || !buflen)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }


  if (_supermicro_oem_temp_level_sensor_supported (manufacturer_id, product_id))
    {
      switch (event_reading_type_code)
	{
	case IPMI_EVENT_READING_TYPE_CODE_OEM_SUPERMICRO_GENERIC:
	  {
	    switch (sensor_type)
	      {
	      case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP:
		{
		  switch (event_bitmask)
		    {
		    case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP_LOW:
		      return (snprintf (buf, buflen, "Low"));
		    case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP_MEDIUM:
		      return (snprintf (buf, buflen, "Medium"));
		    case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP_HIGH:
		      return (snprintf (buf, buflen, "High"));
		    case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP_OVERHEAT:
		      return (snprintf (buf, buflen, "Overheat"));
		    case IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP_NOT_INSTALLED:
		      return (snprintf (buf, buflen, "Not Installed"));
		    }
		}
		break;
	      }
	  }
	  break;

	}
    }

  SET_ERRNO (EINVAL);
  return (-1);
}
