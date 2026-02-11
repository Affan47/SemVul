processYUV_MMX(imageStruct &image, imageStruct &right)
{
  int datasize = image.xsize * image.ysize * image.csize;
  datasize=datasize/sizeof(__m64)+(datasize%sizeof(__m64)!=0);

  __m64 *leftPix =  (__m64*)image.data;
  __m64 *rightPix = (__m64*)right.data;


  const __m64 hi=_mm_setr_pi8(CLAMP(m_Uvalue + m_Urange),
			      CLAMP(m_Yvalue + m_Yrange),
			      CLAMP(m_Vvalue + m_Vrange),
			      CLAMP(m_Yvalue + m_Yrange),
			      CLAMP(m_Uvalue + m_Urange),
			      CLAMP(m_Yvalue + m_Yrange),
			      CLAMP(m_Vvalue + m_Vrange),
			      CLAMP(m_Yvalue + m_Yrange));
  const __m64 lo=_mm_setr_pi8(CLAMP(m_Uvalue - m_Urange),
			      CLAMP(m_Yvalue - m_Yrange),
			      CLAMP(m_Vvalue - m_Vrange),
			      CLAMP(m_Yvalue - m_Yrange),
			      CLAMP(m_Uvalue - m_Urange),
			      CLAMP(m_Yvalue - m_Yrange),
			      CLAMP(m_Vvalue - m_Vrange),
			      CLAMP(m_Yvalue - m_Yrange));

  const __m64 null64=_mm_setzero_si64();

  __m64 r, l, b0, b1;

  if (m_direction) {
    while(datasize--){
      l=leftPix [datasize];
      r=rightPix[datasize];

      b0=_mm_subs_pu8   (lo, l);
      b1=_mm_subs_pu8   (l, hi);
      b0=_mm_cmpeq_pi32 (b0, null64);
      b1=_mm_cmpeq_pi32 (b1, null64);

      b0=_mm_and_si64   (b0, b1);

      b1=_mm_and_si64   (b0, r);
      b0=_mm_andnot_si64(b0, l);

      leftPix[datasize]=_mm_or_si64(b0, b1);
    }
  } else {
    while(datasize--){
      l=leftPix [datasize];
      r=rightPix[datasize];

      b0=_mm_subs_pu8(lo, l);
      b1=_mm_subs_pu8(l, hi);
      b0=_mm_cmpeq_pi32(b0, null64);
      b1=_mm_cmpeq_pi32(b1, null64);

      b0=_mm_and_si64 (b0, b1);

      b1=_mm_and_si64   (b0, l);
      b0=_mm_andnot_si64(b0, r);

      leftPix[datasize]=_mm_or_si64(b0, b1);
    }
  }
  _mm_empty();
}
