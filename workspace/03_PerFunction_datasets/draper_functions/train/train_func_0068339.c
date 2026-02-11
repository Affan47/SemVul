calculateConstants() {
  float ow = (float)((h*src.getWidth()*src.getAspectRatio())/(src.getHeight()*aspectratio));
  float oh = (float)((w*src.getHeight()*aspectratio)/(src.getWidth()*src.getAspectRatio()));

  if (w<ow)
    oh=h;
  else if (h<oh)
    ow=w;

  xfactor=src.getWidth()/ow;
  yfactor=src.getHeight()/oh;
  xoffset=(ow-w)/2;
  yoffset=(oh-h)/2;
}
