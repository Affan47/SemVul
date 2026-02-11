thetaonX(float rerho, float imrho, float X) {
    if(X!=0.)
      return atan2(imrho-1./X, rerho-1.);
    else
      return 0;
}
