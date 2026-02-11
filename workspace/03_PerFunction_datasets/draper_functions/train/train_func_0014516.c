au_ct_hdy (init_data, detected, easter, year, hd_elems, fday, count)
     Bool *init_data;
     const Bool detected;
     int easter;
     const int year;
     int *hd_elems;
     const int fday;
     const int count;


{
  register int day;
  register int i;


  ptr_cc_id = "AU_CT";
  au_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  holiday (*init_data, detected, _(hd_text[HD_GOOD_SATURDAY].ht_text),
	   ptr_cc_id, "+", easter - 1, 0, year, hd_elems, fday, count);
  day = 26;
  i = weekday_of_date (day, MONTH_MAX, year);
  if (i > 5)
    day += 2;
  else if (i == DAY_MIN)
    day++;
  holiday (*init_data, detected, _(hd_text[HD_BOXING_DAY].ht_text),
	   ptr_cc_id, "+", day, MONTH_MAX, year, hd_elems, fday, count);
  day = eval_holiday (DAY_MIN, 6, year, DAY_MIN, TRUE) + DAY_MAX;
  holiday (*init_data, detected, _(hd_text[HD_THE_QUEENS_BIRTHDAY].ht_text),
	   ptr_cc_id, "+", day, 6, year, hd_elems, fday, count);
  day = eval_holiday (DAY_MIN, 3, year, DAY_MIN, TRUE) + (2 * DAY_MAX);
  holiday (*init_data, detected, _(hd_text[HD_CANBERRA_DAY].ht_text),
	   ptr_cc_id, "+", day, 3, year, hd_elems, fday, count);
  day = eval_holiday (DAY_MIN, 8, year, DAY_MIN, TRUE) + (2 * DAY_MAX);
  holiday (*init_data, detected, _(hd_text[HD_BANK_HOLIDAY].ht_text),
	   ptr_cc_id, "+", day, 8, year, hd_elems, fday, count);
  day = eval_holiday (DAY_MIN, 10, year, DAY_MIN, TRUE);
  holiday (*init_data, detected, _(hd_text[HD_LABOUR_DAY].ht_text),
	   ptr_cc_id, "+", day, 10, year, hd_elems, fday, count);
}
