IIT_get_exact_multiple (int *nexactmatches, T this, char *divstring, unsigned int x, unsigned int y, int type) {
  int *exactmatches;
  int index;
  int *matches, nmatches, i, j;
  Interval_T interval;

  *nexactmatches = 0;
  matches = IIT_get(&nmatches,this,divstring,x,y,false);
  for (i = 0; i < nmatches; i++) {
    index = matches[i];
    interval = &(this->intervals[0][index-1]);
    if (Interval_low(interval) == x && Interval_high(interval) == y &&
	Interval_type(interval) == type) {
      (*nexactmatches)++;
    }
  }

  if (*nexactmatches == 0) {
    FREE(matches);
    return (int *) NULL;
  } else {
    exactmatches = (int *) CALLOC(*nexactmatches,sizeof(int));
    j = 0;
    for (i = 0; i < nmatches; i++) {
      index = matches[i];
      interval = &(this->intervals[0][index-1]);
      if (Interval_low(interval) == x && Interval_high(interval) == y &&
	  Interval_type(interval) == type) {
	exactmatches[j++] = index;
      }
    }
    FREE(matches);
    return exactmatches;
  }
}
