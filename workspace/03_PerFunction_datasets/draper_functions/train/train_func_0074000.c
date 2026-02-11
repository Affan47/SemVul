offsetHistory( int minMother, int addMother, int minDaughter,
  int addDaughter) {

  if (addMother < 0 || addDaughter < 0) return;
  if (  mother1Save > minMother  )   mother1Save += addMother;
  if (  mother2Save > minMother  )   mother2Save += addMother;
  if (daughter1Save > minDaughter) daughter1Save += addDaughter;
  if (daughter2Save > minDaughter) daughter2Save += addDaughter;

}
