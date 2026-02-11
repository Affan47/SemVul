ipmi_sensors_oem_intel_node_manager_output_oem_record (ipmi_sensors_state_data_t *state_data,
						       const void *sdr_record,
						       unsigned int sdr_record_len)
{
  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (state_data->prog_data->args->verbose_count >= 2);
  assert (state_data->prog_data->args->interpret_oem_data);

  if (state_data->intel_node_manager.node_manager_data_found)
    {
      uint8_t nm_device_slave_address;
      uint8_t sensor_owner_lun;
      uint8_t channel_number;
      uint8_t nm_health_event_sensor_number;
      uint8_t nm_exception_event_sensor_number;
      uint8_t nm_operational_capabilities_sensor_number;
      uint8_t nm_alert_threshold_exceeded_sensor_number;
      int ret;

      if ((ret = ipmi_sensors_oem_parse_intel_node_manager (state_data,
                                                            sdr_record,
                                                            sdr_record_len,
                                                            &nm_device_slave_address,
                                                            &sensor_owner_lun,
                                                            &channel_number,
                                                            &nm_health_event_sensor_number,
                                                            &nm_exception_event_sensor_number,
                                                            &nm_operational_capabilities_sensor_number,
                                                            &nm_alert_threshold_exceeded_sensor_number)) < 0)
        return (-1);

      if (ret)
	{
	  pstdout_printf (state_data->pstate,
			  "Node Manager Device Slave Address: %Xh\n",
			  nm_device_slave_address);
	  pstdout_printf (state_data->pstate,
			  "Sensor Owner LUN: %Xh\n",
			  sensor_owner_lun);
	  pstdout_printf (state_data->pstate,
			  "Channel Number: %Xh\n",
			  channel_number);
	  pstdout_printf (state_data->pstate,
			  "Node Manager Health Event Sensor Number: %u\n",
			  nm_health_event_sensor_number);
	  pstdout_printf (state_data->pstate,
			  "Node Manager Exception Event Sensor Number: %u\n",
			  nm_exception_event_sensor_number);
	  pstdout_printf (state_data->pstate,
			  "Node Manager Operational Capabilities Sensor Number: %u\n",
			  nm_operational_capabilities_sensor_number);
	  pstdout_printf (state_data->pstate,
			  "Node Manager Alert Threshold Exceeded Sensor Number: %u\n",
			  nm_alert_threshold_exceeded_sensor_number);

	  return (1);
	}
    }

  return (0);
}
