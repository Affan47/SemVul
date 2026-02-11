qh_initstatistics (void) {
  int i;
  realT realx;
  int intx;

#if qh_QHpointer
  if (!(qh_qhstat= (qhstatT *)malloc (sizeof(qhstatT)))) qhull_fatal(33);
#endif

  qhstat next= 0;
  qh_allstatA();
  qh_allstatB();
  qh_allstatC();
  qh_allstatD();
  qh_allstatE();
  qh_allstatF();

  qhstat init[zinc].i= 0;
  qhstat init[zadd].i= 0;
  qhstat init[zmin].i= INT_MAX;
  qhstat init[zmax].i= INT_MIN;
  qhstat init[wadd].r= 0;
  qhstat init[wmin].r= REALmax;
  qhstat init[wmax].r= -REALmax;
  for (i=0; i<ZEND; i++) {
    if (qhstat type[i] > ZTYPEreal) {
      realx= qhstat init[(unsigned char)(qhstat type[i])].r;
      qhstat stats[i].r= realx;
    }else if (qhstat type[i] != zdoc) {
      intx= qhstat init[(unsigned char)(qhstat type[i])].i;
      qhstat stats[i].i= intx;
    }
  }
}
