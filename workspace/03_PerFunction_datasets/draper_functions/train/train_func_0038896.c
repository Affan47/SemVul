expandrow(FXuchar* optr,FXuchar *iptr){
  unsigned char pixel, count;
  while(1){
    pixel=*iptr++;
    count=pixel&0x7f;
    if(count==0) return;
    if(pixel&0x80){
      while(count--){
	*optr=*iptr++;
	optr+=4;
        }
      }
    else{
      pixel=*iptr++;
      while(count--){
	*optr=pixel;
	optr+=4;
        }
      }
    }
  }
