fromYU12(const unsigned char*yuvdata) {
  if(!yuvdata)return;
  size_t pixelnum=xsize*ysize;
  fromYV12((yuvdata), yuvdata+(pixelnum), yuvdata+(pixelnum+(pixelnum>>2)));
}
