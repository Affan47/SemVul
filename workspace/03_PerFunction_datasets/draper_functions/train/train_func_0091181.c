get_y_min(int     xcPix,
          int     ycTracePix,
          double   int_min,
          float** mInImaF,
          int LOC_SAV_BORD_SZ)
{


  int i = 0;
  int y1 =0;
  int  y2 =0;
  float int1 =0;
  float int2 =0;
  float yMin =0;

  yMin=0;


  i= ycTracePix;

  while(mInImaF[i][xcPix]>int_min){
    --i;
  }
  y1=i;
  y2=i+1;


  int1=mInImaF[y1][xcPix];
  int2=mInImaF[y2][xcPix];
  yMin=(float)(y1+(y2-y1)/(int2-int1)*(int_min-int1));
  yMin+=LOC_SAV_BORD_SZ;

  return yMin;

}
