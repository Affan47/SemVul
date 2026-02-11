narrate_spending(char * account, char * currency,
                      double loans_interest_rate,
                      double savings_interest_rate,
                      double inflation_rate)
{
  double balance = get_current_balance(account, currency, 0);
  char * currencystr = get_currency_description(currency);
  time_t rawtime;
  struct tm * timeinfo;
  int year, month, months_remaining;
  double total_receive=0,total_spend=0;
  double average_income = 0;
  double average_spending = 0;
  char * str = 0;

  if (currencystr==0) {
    printf("Unrecognised currency type %s\n", currency);
    return;
  }

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  month = timeinfo->tm_mon + 1;
  year = timeinfo->tm_year + YEAR_BASELINE;

  if (get_annual_cashflow(account, currency,
                          year, month,
                          &total_receive, &total_spend)!=0) {
    average_income = total_receive / 12.0;
    average_spending = total_spend / 12.0;
    if (average_spending>=1) {
      str = get_text_from_identifier(NARRATOR_AVERAGE_SPENDING);
      if (str!=0) {

        printf(str,account,(int)average_spending,currencystr);
        if (balance>0) {

          months_remaining = calc_ETA(average_income,
                                      average_spending, balance,
                                      savings_interest_rate,
                                      inflation_rate);
          if (months_remaining <= 12) {

            str = get_text_from_identifier(NARRATOR_MONTHS_TO_BROKE);
            if (str!=0) {
              printf("\n");
              printf(str,months_remaining);
            }
          }
          else {
            if (months_remaining < MAX_PREDICTION_YEARS*12) {

              str = get_text_from_identifier(NARRATOR_YEARS_TO_BROKE);
              if (str!=0) {
                printf("\n");
                printf(str,months_remaining/12,months_remaining%12);
              }
            }
          }
        }
        else {

          if ((int)average_income>0) {


            months_remaining = calc_ETA(average_income,
                                        average_spending,
                                        balance,
                                        loans_interest_rate,
                                        inflation_rate);
            if (months_remaining <= 12) {

              str = get_text_from_identifier(NARRATOR_MONTHS_TO_REPAID);
              if (str != 0) {
                printf(".  ");
                printf(str,months_remaining);
              }
            }
            else {
              if (months_remaining < MAX_PREDICTION_YEARS*12) {

                str = get_text_from_identifier(NARRATOR_YEARS_TO_REPAID);
                if (str != 0) {
                  printf(".\n");
                  printf(str,months_remaining/12,months_remaining%12);
                }
              }
              else {

                str = get_text_from_identifier(NARRATOR_DELINQUENT);
                if (str != 0) {
                  printf(".\n%s", str);
                }
              }
            }
          }
        }
        printf("\n");
      }
    }
  }
}
