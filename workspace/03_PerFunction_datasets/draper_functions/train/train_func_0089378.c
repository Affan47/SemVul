an_ma_hdy (init_data, detected, easter, year, hd_elems, fday, count)
     Bool *init_data;
     const Bool detected;
     int easter;
     const int year;
     int *hd_elems;
     const int fday;
     const int count;


{
  ptr_cc_id = "AN_MA";
  an_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  holiday (*init_data, detected, _(hd_text[HD_ALL_SAINTS_DAY].ht_text),
	   ptr_cc_id, "+", DAY_MIN, 11, year, hd_elems, fday, count);
  holiday (*init_data, detected, _(hd_text[HD_MARTINIMAS].ht_text),
	   ptr_cc_id, "+", 11, 11, year, hd_elems, fday, count);
  holiday (*init_data, detected, _(hd_text[HD_NATIONAL_HOLIDAY].ht_text),
	   ptr_cc_id, "+", 15, MONTH_MAX, year, hd_elems, fday, count);
  holiday (*init_data, detected, _(hd_text[HD_VICTOR_SCHOELCHER_DAY].ht_text),
	   ptr_cc_id, "+", 21, 7, year, hd_elems, fday, count);
  if (year > 1944)
    holiday (*init_data, detected, _(hd_text[HD_ARMISTICE_DAY].ht_text),
	     ptr_cc_id, "+", 8, 5, year, hd_elems, fday, count);
}
