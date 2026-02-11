getNumIntegers () const
{
  if (numberIntegers_>=0) {

    return numberIntegers_;
  } else {

    const int numCols = getNumCols() ;
    int numIntegers = 0 ;
    for (int i = 0 ; i < numCols ; ++i) {
      if (!isContinuous(i)) {
	numIntegers++ ;
      }
    }
    return (numIntegers) ;
  }
}
