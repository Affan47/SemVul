us_vt_hdy (init_data, detected, easter, year, hd_elems, fday, count)
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


  ptr_cc_id = "US_VT";
  observe_us_hdy = SAFR_SUMO;
  us_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  day = 16;
  i = weekday_of_date (day, 8, year);
  if (i == DAY_MAX)
    day++;
  else if (i == 6)
    day--;
  holiday (*init_data, detected, _(hd_text[HD_BENNINGTON_BATTLE_DAY].ht_text),
	   ptr_cc_id, "+", day, 8, year, hd_elems, fday, count);
  day = 12;
  i = weekday_of_date (day, 2, year);
  if (i == DAY_MAX)
    day++;
  else if (i == 6)
    day--;
  holiday (*init_data, detected,
	   _(hd_text[HD_PRESIDENT_LINCOLNS_BIRTHDAY].ht_text), ptr_cc_id, "+",
	   day, 2, year, hd_elems, fday, count);
  day = eval_holiday (DAY_MIN, 3, year, 2, TRUE);
  holiday (*init_data, detected, _(hd_text[HD_TOWN_MEETING_DAY].ht_text),
	   ptr_cc_id, "+", day, 3, year, hd_elems, fday, count);
}
