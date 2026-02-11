getScanLineHorz(short* red, short* green, short* blue,
				     float x1, float y1,
				     float x2, float y2, int npixels) {
  switch (degree) {
  case 0:
    src.getScanLineHorz(red,green,blue,x1,y1,x2,y2,npixels);
    return;
  case 180:
    src.getScanLineHorz(red,green,blue,src.getWidth()-x1,src.getHeight()-y2,
			src.getWidth()-x2,src.getHeight()-y1,npixels);
    return;
  case 90:
    src.getScanLineVert(red,green,blue,y1,src.getHeight()-x1,
			y2,src.getHeight()-x2,npixels);
    return;
  case 270:
    src.getScanLineVert(red,green,blue,src.getWidth()-y2,x1,
			src.getWidth()-y1,x2,npixels);
    return;
  }
  GImage::getScanLineHorz(red,green,blue,x1,y1,x2,y2,npixels);
}
