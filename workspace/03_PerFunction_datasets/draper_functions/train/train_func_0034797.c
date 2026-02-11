adns__isort(void *array, int nobjs, int sz, void *tempbuf,
		 int (*needswap)(void *context, const void *a, const void *b),
		 void *context) {
  byte *data= array;
  int i, place;

  for (i=0; i<nobjs; i++) {
    for (place= i;
	 place>0 && needswap(context, data + (place-1)*sz, data + i*sz);
	 place--);
    if (place != i) {
      memcpy(tempbuf, data + i*sz, sz);
      memmove(data + (place+1)*sz, data + place*sz, (i-place)*sz);
      memcpy(data + place*sz, tempbuf, sz);
    }
  }
}
