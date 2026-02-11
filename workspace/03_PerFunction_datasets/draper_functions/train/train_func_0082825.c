factorizePart1 ( int numberOfRows,
				   int ,
				   CoinBigIndex numberOfElements,
				   int * indicesRow[],
				   int * indicesColumn[],
				   CoinFactorizationDouble * elements[],
				   double areaFactor)
{

  gutsOfDestructor();
  gutsOfInitialize(2);
  if (areaFactor)
    areaFactor_ = areaFactor;
  CoinBigIndex numberElements = 3 * numberOfRows + 3 * numberOfElements + 20000;
  getAreas ( numberOfRows, numberOfRows, numberElements,
	     2 * numberElements );

  *indicesRow = indexRowU_.array() ;
  *indicesColumn = indexColumnU_.array() ;
  *elements = elementU_.array() ;
  lengthU_ = numberOfElements;
  maximumU_ = numberElements;
  return 0;
}
