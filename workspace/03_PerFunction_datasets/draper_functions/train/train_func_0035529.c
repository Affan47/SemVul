de_sn_hdy (init_data, detected, easter, year, hd_elems, fday, count)
     Bool *init_data;
     const Bool detected;
     int easter;
     const int year;
     int *hd_elems;
     const int fday;
     const int count;


{
  register int day;


  ptr_cc_id = "DE_SN";
  use_other_cc = !use_other_cc;
  de_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  use_other_cc = !use_other_cc;
  holiday (*init_data, detected,
	   _(hd_text[HD_FEAST_OF_CORPUS_CHRISTI].ht_text), ptr_cc_id,
	   DIS_HLS_PREF2, easter + 60, 0, year, hd_elems, fday, count);
  day = weekday_of_date (DAY_MIN, 11, year);
  day = (day < 3) ? 18 - day : 25 - day;
  holiday (*init_data, detected,
	   _(hd_text[HD_DAY_OF_PRAYER_AND_REPENTANCE].ht_text), ptr_cc_id,
	   "+", day, 11, year, hd_elems, fday, count);
  if (year > 1516)
    holiday (*init_data, detected, _(hd_text[HD_REFORMATION_DAY].ht_text),
	     ptr_cc_id, DIS_HLS_PREF2, dvec[10 - 1], 10, year, hd_elems, fday,
	     count);
  if (year > 1989)
    holiday (*init_data, detected, _(hd_text[HD_GERMAN_UNITY_DAY].ht_text),
	     ptr_cc_id, "+", 3, 10, year, hd_elems, fday, count);
}
