ipmi_sel_parse_output_dell_event_data2_class_oem (ipmi_sel_parse_ctx_t ctx,
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
  assert (ctx->manufacturer_id == IPMI_IANA_ENTERPRISE_ID_DELL);
  assert (sel_parse_entry);
  assert (tmpbuf);
  assert (tmpbuflen);
  assert (!(flags & ~IPMI_SEL_PARSE_STRING_MASK));
  assert (flags & IPMI_SEL_PARSE_STRING_FLAGS_INTERPRET_OEM_DATA);
  assert (wlen);
  assert (system_event_record_data);


  if ((ctx->product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_2900
       || ctx->product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_2950
       || ctx->product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_R610
       || ctx->product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_R710)
      && system_event_record_data->event_type_code == IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_OEM_DIAGNOSTIC_EVENT_DATA
      && system_event_record_data->sensor_type == IPMI_SENSOR_TYPE_OEM_DELL_LINK_TUNING)
    {
      uint16_t register_offset;

      register_offset = system_event_record_data->event_data2;
      register_offset |= (system_event_record_data->offset_from_event_reading_type_code) << 8;

      snprintf (tmpbuf,
                tmpbuflen,
                "Register Offset = %Xh",
                register_offset);

      return (1);
    }

  return (0);
}
