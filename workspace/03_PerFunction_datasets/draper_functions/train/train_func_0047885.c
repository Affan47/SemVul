Load( MemBuffer &file ) {
  p_id = file.Read8();
  p_type = file.Read8();
  p_success = file.Read8();
  p_briefing = file.Read8();
  p_name_id = file.Read8();

  unsigned char len = file.Read8();
  p_password = StringUtil::crypt( file.ReadS(len) );

  p_col_light.r = file.Read8();
  p_col_light.g = file.Read8();
  p_col_light.b = file.Read8();
  p_col_dark.r = file.Read8();
  p_col_dark.g = file.Read8();
  p_col_dark.b = file.Read8();

  p_mode = MODE_IDLE;
  p_remote = false;
  p_units = 0;
  return 0;
}
