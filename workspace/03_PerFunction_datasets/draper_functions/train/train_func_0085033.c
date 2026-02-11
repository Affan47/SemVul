wc2utf(FXwchar* dst,FXint ndst,FXwchar wc){
  if(ndst<1) return -1;
  dst[0]=wc;
  return 1;
  }
