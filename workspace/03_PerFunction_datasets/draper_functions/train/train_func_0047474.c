ch_be_hdy (init_data, detected, easter, year, hd_elems, fday, count)
     Bool *init_data;
     const Bool detected;
     int easter;
     const int year;
     int *hd_elems;
     const int fday;
     const int count;


{
  register int i;


  ptr_cc_id = "CH_BE";
  ch_base_hdy (init_data, detected, easter, year, hd_elems, fday, count);
  for (i = 3; i; i--)
    holiday (*init_data, detected, _(hd_text[HD_CARNIVAL].ht_text),
	     ptr_cc_id, "+", easter - 42 - i, 0, year, hd_elems, fday, count);
}
