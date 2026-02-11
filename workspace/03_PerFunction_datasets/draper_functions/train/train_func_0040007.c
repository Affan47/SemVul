sigmaKin() {


  pickFinal();


  for (int i = 0; i < 2; i++) {


    pCM[0] = Vec4( 0., 0.,  0.5 * mH, 0.5 * mH);
    pCM[1] = Vec4( 0., 0., -0.5 * mH, 0.5 * mH);
    mapFinal();


    swap(pCM[i], pCM[2]);


    sigma[i] = 3. * (3. / 8.) * m2Calc();

  }

}
