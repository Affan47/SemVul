ipmi_sel_parse_output_quanta_event_data2_discrete_oem (ipmi_sel_parse_ctx_t ctx,
                                                       struct ipmi_sel_parse_entry *sel_parse_entry,
                                                       uint8_t sel_record_type,
                                                       char *tmpbuf,
                                                       unsigned int tmpbuflen,
                                                       unsigned int flags,
                                                       unsigned int *wlen,
                                                       struct ipmi_sel_system_event_record_data *system_event_record_data)
{
  assert (ctx);
  assert (ctx->magic == IPMI_SEL_PARSE_CTX_MAGIC);
  assert (ctx->manufacturer_id == IPMI_IANA_ENTERPRISE_ID_QUANTA);
  assert (sel_parse_entry);
  assert (tmpbuf);
  assert (tmpbuflen);
  assert (!(flags & ~IPMI_SEL_PARSE_STRING_MASK));
  assert (flags & IPMI_SEL_PARSE_STRING_FLAGS_INTERPRET_OEM_DATA);
  assert (wlen);
  assert (system_event_record_data);
  assert (system_event_record_data->event_data2_flag == IPMI_SEL_EVENT_DATA_OEM_CODE);


  if (ctx->product_id == IPMI_QUANTA_PRODUCT_ID_S99Q)
    {
      if (system_event_record_data->generator_id == IPMI_GENERATOR_ID_OEM_QUANTA_ERROR
          && system_event_record_data->sensor_type == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT
          && system_event_record_data->sensor_number == IPMI_SENSOR_NUMBER_OEM_QUANTA_PCI_SENSORID
          && system_event_record_data->event_type_code == IPMI_EVENT_READING_TYPE_CODE_SENSOR_SPECIFIC
          && (system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_PCI_PERR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_PCI_SERR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_CORRECTABLE_ERROR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_UNCORRECTABLE_ERROR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_FATAL_ERROR))
        {
          uint8_t device, function;

          device = (system_event_record_data->event_data2 & IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_OEM_QUANTA_EVENT_DATA2_DEVICE_NUMBER_BITMASK);
          device >>= IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_OEM_QUANTA_EVENT_DATA2_DEVICE_NUMBER_SHIFT;

          function = (system_event_record_data->event_data2 & IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_OEM_QUANTA_EVENT_DATA2_FUNCTION_NUMBER_BITMASK);
          function >>= IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_OEM_QUANTA_EVENT_DATA2_FUNCTION_NUMBER_SHIFT;

          snprintf (tmpbuf,
                    tmpbuflen,
                    "Device %u, Function %u",
                    device,
                    function);

          return (1);
        }

      if (system_event_record_data->generator_id == IPMI_GENERATOR_ID_OEM_QUANTA_ERROR
          && system_event_record_data->sensor_type == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT
          && (system_event_record_data->sensor_number == IPMI_SENSOR_NUMBER_OEM_QUANTA_QPI_SENSORID
              || system_event_record_data->sensor_number == IPMI_SENSOR_NUMBER_OEM_QUANTA_INT_SENSORID)
          && system_event_record_data->event_type_code == IPMI_EVENT_READING_TYPE_CODE_SENSOR_SPECIFIC
          && (system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_CORRECTABLE_ERROR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_UNCORRECTABLE_ERROR
              || system_event_record_data->offset_from_event_reading_type_code == IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT_BUS_FATAL_ERROR))
        {
          snprintf (tmpbuf,
                    tmpbuflen,
                    "Local Error Bit %u",
                    system_event_record_data->event_data2);

          return (1);
        }

    }

  return (0);
}
