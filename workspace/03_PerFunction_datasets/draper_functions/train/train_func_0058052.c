zscii_output_char_to_z_ucs(zscii zscii_output)
{
  z_ucs result = -1;

  TRACE_LOG("Converting ZSCII-Output(!)-Char %d to UCS-4.\n", zscii_output);

  if (zscii_output == 0)
    result = 0;
  else if (zscii_output == 9)
    result = latin1_char_to_zucs_char('\t');
  else if (zscii_output == 11)
    result = latin1_char_to_zucs_char('.');
  else if (zscii_output == 13)
    result = Z_UCS_NEWLINE;
  else if ((zscii_output >= 32) && (zscii_output <= 126))
    result = (z_ucs)zscii_output;
  else if ((zscii_output >= 155) && (zscii_output <= 251))
    result = zscii_extra_char_to_unicode(zscii_output);
  else
    i18n_translate_and_exit(
        libfizmo_module_name,
        i18n_libfizmo_INVALID_ZSCII_OUTPUT_CODE_P0D,
        -1,
        (long)zscii_output);

  TRACE_LOG("Result: %d.\n", (unsigned)result);

  return result;
}
