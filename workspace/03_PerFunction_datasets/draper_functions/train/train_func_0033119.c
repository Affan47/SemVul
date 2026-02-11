packF1(action* a,buffer *b) {


grib_int_t count;
grib_int_t* flag;

  flag = (grib_int_t*) malloc(sizeof(grib_int_t));
  if( flag == NULL ) {
    perror("packF1: malloc failed in packF1");
    exit(1);
  }

  *flag = atol(a->count);
  (a->value) = *flag;
  updateOffsets(a,b,&count);

  MOVE1BYTE((b->packed),flag);
  (b->packed)++;

  b->totalPackedBytes++;
  return a->next;
}
