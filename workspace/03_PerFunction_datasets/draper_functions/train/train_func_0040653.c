show_summary_balance(char * account)
{
  int i,retval = 1;
  char total_spend[MAX_CURRENCIES][30];
  char total_receive[MAX_CURRENCIES][30];
  char total_balance[MAX_CURRENCIES][30];
  char currency[MAX_CURRENCIES][30];

  if (strlen(account)==0) {
    settings_set_account(get_text_from_identifier(SETTINGS_DEFAULT_CURRENT_ACCOUNT));
    if (strlen(get_text_from_identifier(SETTINGS_DEFAULT_CURRENT_ACCOUNT))==0) {
      printf("Unable to get default account name\n");
      return 0;
    }
    account = settings_get_account();
  }

  retval = get_balance(account,(char**)currency,(char**)total_spend,
                       (char**)total_receive,(char**)total_balance);
  if (retval!=0) {
    i=0;
    while (i<MAX_CURRENCIES) {
      if (atof((char*)&total_spend[i]) +
          atof((char*)&total_receive[i]) == 0) {
        break;
      }
      printf(get_text_from_identifier(SUMMARY_BALANCE),
             (char*)&currency[i],(char*)&total_receive[i],
             (char*)&total_spend[i],(char*)&total_balance[i]);
      printf("\n");
      i++;
    }
  }
  return retval;
}
