packLIST(action* a,buffer *b) {


grib_int_t count = a->reference->value;
grib_int_t i;

  (a->sum) = 0;
  for(i = 0; i < count; i++) {
    encode(a->next,b);
  }

  return a->end->next;
}
