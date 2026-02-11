dualChannelFiltering(
        const FIXP_DBL *const      pQmfReal,
        const FIXP_DBL *const      pQmfImag,
        const INT *const           pReadIdx,
        FIXP_DBL *const            mHybridReal,
        FIXP_DBL *const            mHybridImag,
        const INT                  invert
        )
{
    const FIXP_HTB *p = HybFilterCoef2;

    FIXP_DBL  r1, r6;
    FIXP_DBL  i1, i6;


    r1  = fMultDiv2(p[1], pQmfReal[pReadIdx[1]]) + fMultDiv2(p[1], pQmfReal[pReadIdx[11]]) ;
    i1  = fMultDiv2(p[1], pQmfImag[pReadIdx[1]]) + fMultDiv2(p[1], pQmfImag[pReadIdx[11]]) ;
    r1 += fMultDiv2(p[3], pQmfReal[pReadIdx[3]]) + fMultDiv2(p[3], pQmfReal[pReadIdx[ 9]]) ;
    i1 += fMultDiv2(p[3], pQmfImag[pReadIdx[3]]) + fMultDiv2(p[3], pQmfImag[pReadIdx[ 9]]) ;
    r1 += fMultDiv2(p[5], pQmfReal[pReadIdx[5]]) + fMultDiv2(p[5], pQmfReal[pReadIdx[ 7]]) ;
    i1 += fMultDiv2(p[5], pQmfImag[pReadIdx[5]]) + fMultDiv2(p[5], pQmfImag[pReadIdx[ 7]]) ;
    r6  = fMultDiv2(p[6], pQmfReal[pReadIdx[6]]) ;
    i6  = fMultDiv2(p[6], pQmfImag[pReadIdx[6]]) ;

    if (invert) {
      mHybridReal[1] = (r1 + r6) << 1;
      mHybridImag[1] = (i1 + i6) << 1;

      mHybridReal[0] = (r6 - r1) << 1;
      mHybridImag[0] = (i6 - i1) << 1;
    }
    else {
      mHybridReal[0] = (r1 + r6) << 1;
      mHybridImag[0] = (i1 + i6) << 1;

      mHybridReal[1] = (r6 - r1) << 1;
      mHybridImag[1] = (i6 - i1) << 1;
    }
}
