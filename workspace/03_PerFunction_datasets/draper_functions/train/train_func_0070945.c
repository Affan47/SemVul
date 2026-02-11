processRGBA_MMX (imageStruct &image, imageStruct &right){
  int datasize =   image.xsize * image.ysize * image.csize;
  __m64*leftPix =  (__m64*)image.data;
  __m64*rightPix = (__m64*)right.data;

  datasize=datasize/sizeof(__m64)+(datasize%sizeof(__m64)!=0);
  __m64 rGain = _mm_set1_pi16((short)rightGain);
  __m64 lGain = _mm_set1_pi16((short)imageGain);
  __m64 null64 =   _mm_setzero_si64();

  __m64 l1, r1, l2, r2;
  while (datasize--) {
    l1=leftPix [datasize];
    r1=rightPix[datasize];

    l2=_mm_unpackhi_pi8 (l1, null64);
    l1=_mm_unpacklo_pi8 (l1, null64);
    r2=_mm_unpackhi_pi8 (r1, null64);
    r1=_mm_unpacklo_pi8 (r1, null64);

    l1 = _mm_mullo_pi16(l1, lGain);
    l2 = _mm_mullo_pi16(l2, lGain);
    r1 = _mm_mullo_pi16(r1, rGain);
    r2 = _mm_mullo_pi16(r2, rGain);

    l1 = _mm_adds_pu16 (l1, r1);
    l2 = _mm_adds_pu16 (l2, r2);

    l1 = _mm_srli_pi16 (l1, 8);
    l2 = _mm_srli_pi16 (l2, 8);
    l1 = _mm_packs_pu16(l1, l2);
    leftPix[datasize]=l1;
  }
  _mm_empty();
}
