thousands_sep_to_STACK (char* sep1000) {
  int ii;
  for (ii=0; sep1000[ii]; ii++) pushSTACK(fixnum(sep1000[ii]));
  pushSTACK(Fixnum_0); value1 = vectorof(ii+1); pushSTACK(value1);
}
