us_nh_hdy (init_data, detected, easter, year, hd_elems, fday, count)
     Bool *init_data;
     const Bool detected;
     int easter;
     const int year;
     int *hd_elems;
     const int fday;
     const int count;


{
  ptr_cc_id = "US_NH";
  observe_us_hdy = SASA_SUSU;
  us_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  if (year > 1844)
    {
      register int day;


      day = eval_holiday (DAY_MIN, 11, year, DAY_MIN, TRUE) + 1;
      holiday (*init_data, detected, _(hd_text[HD_ELECTION_DAY].ht_text),
	       ptr_cc_id, "+", day, 11, year, hd_elems, fday, count);
    }
}
