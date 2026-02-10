pTnext( Event& event, double pTbegAll, double pTendAll) {


  dipSel  = 0;
  iDipSel = -1;
  double pT2sel = pTendAll * pTendAll;
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    TimeDipoleEnd& dip = dipEnd[iDip];


    useLocalRecoilNow = !(globalRecoil && dip.system == 0
      && partonSystemsPtr->sizeOut(0) <= nMaxGlobalRecoil);


    dip.mRad   = event[dip.iRadiator].m();
    if (useLocalRecoilNow) {
      dip.mRec = event[dip.iRecoiler].m();
      dip.mDip = m( event[dip.iRadiator], event[dip.iRecoiler] );


    } else {
      Vec4 pSumGlobal;
      for (int i = 0; i < partonSystemsPtr->sizeOut( dip.system); ++i) {
        int ii = partonSystemsPtr->getOut( dip.system, i);
        if (ii !=  dip.iRadiator) pSumGlobal += event[ii].p();
      }
      dip.mRec = pSumGlobal.mCalc();
      dip.mDip = m( event[dip.iRadiator].p(), pSumGlobal);
    }
    dip.m2Rad  = pow2(dip.mRad);
    dip.m2Rec  = pow2(dip.mRec);
    dip.m2Dip  = pow2(dip.mDip);


    dip.m2DipCorr    = pow2(dip.mDip - dip.mRec) - dip.m2Rad;
    double pTbegDip  = min( pTbegAll, dip.pTmax );
    double pT2begDip = min( pow2(pTbegDip), 0.25 * dip.m2DipCorr);


    dip.pT2 = 0.;
    if (pT2begDip > pT2sel) {
      if      (dip.colType != 0)
        pT2nextQCD(pT2begDip, pT2sel, dip, event);
      else if (dip.chgType != 0 || dip.gamType != 0)
        pT2nextQED(pT2begDip, pT2sel, dip, event);
      else if (dip.colvType != 0)
        pT2nextHV(pT2begDip, pT2sel, dip, event);


      if (dip.pT2 > pT2sel) {
        pT2sel  = dip.pT2;
        dipSel  = &dip;
        iDipSel = iDip;
      }
    }
  }


  return (dipSel == 0) ? 0. : sqrt(pT2sel);

}
