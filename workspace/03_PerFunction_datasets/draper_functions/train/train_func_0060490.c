Skew(float xgain, float ygain, long xpivot, long ypivot, bool bEnableInterpolation)
{
	if (!pDib) return false;
	float nx,ny;

	CxImage tmp(*this);
	if (!tmp.IsValid()){
		strcpy(info.szLastError,tmp.GetLastError());
		return false;
	}

	long xmin,xmax,ymin,ymax;
	if (pSelection){
		xmin = info.rSelectionBox.left; xmax = info.rSelectionBox.right;
		ymin = info.rSelectionBox.bottom; ymax = info.rSelectionBox.top;
	} else {
		xmin = ymin = 0;
		xmax = head.biWidth; ymax=head.biHeight;
	}
	for(long y=ymin; y<ymax; y++){
		info.nProgress = (long)(100*(y-ymin)/(ymax-ymin));
		if (info.nEscape) break;
		for(long x=xmin; x<xmax; x++){
#if CXIMAGE_SUPPORT_SELECTION
			if (BlindSelectionIsInside(x,y))
#endif
			{
				nx = x + (xgain*(y - ypivot));
				ny = y + (ygain*(x - xpivot));
#if CXIMAGE_SUPPORT_INTERPOLATION
				if (bEnableInterpolation){
					tmp.SetPixelColor(x,y,GetPixelColorInterpolated(nx, ny, CxImage::IM_BILINEAR, CxImage::OM_BACKGROUND),true);
				} else
#endif
				{
					if (head.biClrUsed==0){
						tmp.SetPixelColor(x,y,GetPixelColor((long)nx,(long)ny));
					} else {
						tmp.SetPixelIndex(x,y,GetPixelIndex((long)nx,(long)ny));
					}
#if CXIMAGE_SUPPORT_ALPHA
					tmp.AlphaSet(x,y,AlphaGet((long)nx,(long)ny));
#endif
				}
			}
		}
	}
	Transfer(tmp);
	return true;
}
