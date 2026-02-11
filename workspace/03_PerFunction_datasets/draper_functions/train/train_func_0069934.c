Pete_HalfTone_CalcCorners(int cWidth,int nHeight,float AngleRadians,int nCellSize,
	SPete_HalfTone_Point* poutLeft,
	SPete_HalfTone_Point* poutRight,
	SPete_HalfTone_Point* poutTop,
	SPete_HalfTone_Point* poutBottom) {

  const int nHalfWidth=(cWidth/2);
  const int nHalfHeight=(nHeight/2);
  const int nHalfWidthFP=(nHalfWidth<<nFPShift);
  const int nHalfHeightFP=(nHalfHeight<<nFPShift);

  const int nCellSizeFP=(nCellSize<<nFPShift);
  const int nXExtentFP=nHalfWidthFP+(2*nCellSizeFP);
  const int nYExtentFP=nHalfHeightFP+(2*nCellSizeFP);

  SPete_HalfTone_Point OriginalCorners[4]={
    {-nXExtentFP,-nYExtentFP},
    {nXExtentFP,-nYExtentFP},
    {-nXExtentFP,nYExtentFP},
    {nXExtentFP,nYExtentFP},
  };
  SPete_HalfTone_Point RotatedCorners[4];

  int nCount;
  for (nCount=0; nCount<4; nCount+=1) {
    Rotate(	&OriginalCorners[nCount],
		&RotatedCorners[nCount],
		-AngleRadians);
  }

  GetRasterizationPoints(
			 &RotatedCorners[0],
			 poutLeft,
			 poutRight,
			 poutTop,
			 poutBottom);
}
