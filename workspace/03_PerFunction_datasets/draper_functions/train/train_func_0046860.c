c3745_refresh_systemid(c3745_t *router)
{
  if (router->board_id[0] == 0x00) return(0);
  m_uint8_t buf[11];
  parse_board_id(buf,router->board_id,11);
  cisco_eeprom_set_region(&router->sys_eeprom[2] ,72,buf,11);
  return (0);
}
