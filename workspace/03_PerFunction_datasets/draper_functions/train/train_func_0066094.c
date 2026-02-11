rtensor_Multiply( rtensor ret, rtensor m1, rtensor m2 )
{
  int i, j, k;
  rtensor temp;


  if( ret == m1 || ret == m2 )
    {
      for( i = 0; i < 3; ++i )
        for( j = 0; j < 3; ++j )
          {
            temp[i][j] = 0;
            for( k = 0; k < 3; ++k )
              temp[i][j] += m1[i][k] * m2[k][j];
          }

      for( i = 0; i < 3; ++i )
        for( j = 0; j < 3; ++j )
          ret[i][j] = temp[i][j];
    }
  else
    {
      for( i = 0; i < 3; ++i )
        for( j = 0; j < 3; ++j )
          {
            ret[i][j] = 0;
            for( k = 0; k < 3; ++k )
              ret[i][j] += m1[i][k] * m2[k][j];
          }
    }
}
