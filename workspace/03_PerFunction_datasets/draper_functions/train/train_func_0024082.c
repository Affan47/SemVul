mass() {


  if (modeBWnow == 0) return m0Save;
  double mNow, m2Now;


  if (modeBWnow == 1) {
     mNow = m0Save + 0.5 * mWidthSave
       * tan( atanLow + atanDif * particleDataPtr->rndmPtr->flat() );


  } else if (modeBWnow == 2) {
    double mWidthNow, fixBW, runBW;
    double m0ThrS = m0Save*m0Save - mThr*mThr;
    do {
      mNow = m0Save + 0.5 * mWidthSave
        * tan( atanLow + atanDif * particleDataPtr->rndmPtr->flat() );
      mWidthNow = mWidthSave * sqrtpos( (mNow*mNow - mThr*mThr) / m0ThrS );
      fixBW = mWidthSave / (pow2(mNow - m0Save) + pow2(0.5 * mWidthSave));
      runBW = mWidthNow / (pow2(mNow - m0Save) + pow2(0.5 * mWidthNow));
    } while (runBW < particleDataPtr->rndmPtr->flat()
      * particleDataPtr->maxEnhanceBW * fixBW);


  } else if (modeBWnow == 3) {
    m2Now = m0Save*m0Save + m0Save * mWidthSave
      * tan( atanLow + atanDif * particleDataPtr->rndmPtr->flat() );
    mNow = sqrtpos( m2Now);


  } else {
    double mwNow, fixBW, runBW;
    double m2Ref = m0Save * m0Save;
    double mwRef = m0Save * mWidthSave;
    double m2Thr = mThr * mThr;
    do {
      m2Now = m2Ref + mwRef * tan( atanLow + atanDif
        * particleDataPtr->rndmPtr->flat() );
      mNow = sqrtpos( m2Now);
      mwNow = mNow * mWidthSave
        * sqrtpos( (m2Now - m2Thr) / (m2Ref - m2Thr) );
      fixBW = mwRef / (pow2(m2Now - m2Ref) + pow2(mwRef));
      runBW = mwNow / (pow2(m2Now - m2Ref) + pow2(mwNow));
    } while (runBW < particleDataPtr->rndmPtr->flat()
      * particleDataPtr->maxEnhanceBW * fixBW);
  }


  return mNow;
}
