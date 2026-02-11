decode_display_descriptor (const uchar *desc,
			   MonitorInfo *info)
{
  switch (desc[0x03])
    {
    case 0xFC:
      decode_lf_string (desc + 5, 13, info->dsc_product_name);
      break;
    case 0xFF:
      decode_lf_string (desc + 5, 13, info->dsc_serial_number);
      break;
    case 0xFE:
      decode_lf_string (desc + 5, 13, info->dsc_string);
      break;
    case 0xFD:

      break;
    case 0xFB:

      break;
    case 0xFA:

      break;
    case 0xF9:

      break;
    case 0xF8:

      break;
    case 0xF7:

      break;
    case 0x10:
      break;
    }
}
