check_counter(unsigned short *counter_check,
                          char flag_sign_fct)
{


  if (*counter_check == MGTH_QUERY_SIZE && flag_sign_fct == 'q')
  {
    *counter_check = 0;
  }
  if (*counter_check == MGTH_HIT_SIZE && flag_sign_fct == 'h')
  {
    *counter_check = 0;
  }
  if (*counter_check == MGTH_HIT_TO_QUERY_SIZE && flag_sign_fct == 't')
  {
    *counter_check = 0;
  }
}
