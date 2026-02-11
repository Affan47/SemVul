set_text_style(z_style style_data)
{
  attr_t attrs;

  TRACE_LOG("Output style, style_data %d.\n", style_data);

  attrs = ncursesw_z_style_to_attr_t(style_data);

  if ((int)attrset(attrs) == ERR)
  {
    i18n_translate_and_exit(
        fizmo_ncursesw_module_name,
        i18n_ncursesw_FUNCTION_CALL_P0S_ABORTED_DUE_TO_ERROR,
        -0x2fff,
        "wattrset");
  }
}
