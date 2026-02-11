mmx_fv_1 ( short* &q, short* e, int s, int s3 )
{
  while (q<e && (((long)q)&0x7))
    {
      int a = (int)q[-s] + (int)q[s];
      int b = (int)q[-s3] + (int)q[s3];
      *q -= (((a<<3)+a-b+8)>>4);
      q++;
    }
  while (q+3<e)
    {
      MMXar( movq,       q-s,mm0);
      MMXar( movq,       q+s,mm2);
      MMXrr( movq,       mm0,mm1);
      MMXrr( punpcklwd,  mm2,mm0);
      MMXrr( punpckhwd,  mm2,mm1);
      MMXar( pmaddwd,    w9,mm0);
      MMXar( pmaddwd,    w9,mm1);
      MMXar( movq,       q-s3,mm2);
      MMXar( movq,       q+s3,mm4);
      MMXrr( movq,       mm2,mm3);
      MMXrr( punpcklwd,  mm4,mm2);
      MMXrr( punpckhwd,  mm4,mm3);
      MMXar( pmaddwd,    w1,mm2);
      MMXar( pmaddwd,    w1,mm3);
      MMXar( paddd,      d8,mm0);
      MMXar( paddd,      d8,mm1);
      MMXrr( psubd,      mm2,mm0);
      MMXrr( psubd,      mm3,mm1);
      MMXir( psrad,      4,mm0);
      MMXar( movq,       q,mm7);
      MMXir( psrad,      4,mm1);
      MMXrr( packssdw,   mm1,mm0);
      MMXrr( psubw,      mm0,mm7);
      MMXra( movq,       mm7,q);
#if defined(_MSC_VER) && defined(_DEBUG)
      MMXemms;
#endif
      q += 4;
    }
}
