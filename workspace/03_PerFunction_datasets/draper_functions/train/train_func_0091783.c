AddPoint( int npts, int * pts )
{
  if ( currentPoint >= pointsPerList )
    {
    if (  ( currentList + 1 )  >=  listSize  )
      {
      TableBasedClipperCentroidPointEntry ** tmpList = new
      TableBasedClipperCentroidPointEntry * [ 2 * listSize ];

      for ( int i = 0; i < listSize; i ++ )
        {
        tmpList[i] = list[i];
        }

      for (int i = listSize; i < listSize * 2; i ++ )
        {
        tmpList[i] = NULL;
        }

      listSize *= 2;
      delete [] list;
      list = tmpList;
      }

    currentList ++;
    list[ currentList ] = new TableBasedClipperCentroidPointEntry
                              [ pointsPerList ];
    currentPoint = 0;
    }

  list[ currentList ][ currentPoint ].nPts = npts;
  for ( int i = 0; i < npts; i ++ )
    {
    list[ currentList ][ currentPoint ].ptIds[i] = pts[i];
    }
  currentPoint ++;

  return ( GetTotalNumberOfPoints() - 1 );
}
