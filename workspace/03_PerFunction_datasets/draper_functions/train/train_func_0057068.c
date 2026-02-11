IIT_exists_with_divno_typed_signed (T this, int divno, unsigned int x, unsigned int y, int type, int sign) {
  int match;
  int lambda;
  int min1, max1 = 0, min2, max2 = 0;
  Interval_T interval;

  if (divno < 0) {

    return false;
  }
  min1 = min2 = this->nintervals[divno] + 1;

  debug(printf("Entering IIT_exists_with_divno_typed_signed with divno %d and query %u %u\n",divno,x,y));
  fnode_query_aux(&min1,&max1,this,divno,0,x);
  fnode_query_aux(&min2,&max2,this,divno,0,y);
  debug(printf("min1=%d max1=%d  min2=%d max2=%d\n",min1,max1,min2,max2));

  for (lambda = min1; lambda <= max2; lambda++) {
    match = this->sigmas[divno][lambda];
    interval = &(this->intervals[divno][match - 1]);
    if (Interval_low(interval) == x && Interval_high(interval) == y &&
	Interval_type(interval) == type && Interval_sign(interval) == sign) {
      return true;
    }

    match = this->omegas[divno][lambda];
    interval = &(this->intervals[divno][match - 1]);
    if (Interval_low(interval) == x && Interval_high(interval) == y &&
	Interval_type(interval) == type && Interval_sign(interval) == sign) {
      return true;
    }
  }

  return false;
}
