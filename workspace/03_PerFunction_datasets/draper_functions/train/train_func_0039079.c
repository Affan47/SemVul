process_message(unsigned long type,unsigned long *body)
{
  switch(type)
  {
  case M_NEW_DESK:
    new_desk = body[0];
    RedrawWindow(&main_win,0, -1, num_rows, num_columns);
    break;
  case M_END_WINDOWLIST:
    RedrawWindow(&main_win,0, -1, num_rows, num_columns);
  case M_MAP:
    swallow(body);
  case M_RES_NAME:
  case M_RES_CLASS:
  case M_WINDOW_NAME:
    CheckForHangon(body);
    break;
  case M_CONFIG_INFO:
    handle_config_info_packet((unsigned long*)body);
    break;
  default:
    break;
  }
}
