sigmaHat() {


  if (abs(id1) != idOld && abs(id2) != idOld) return 0.;


  return (id1 == idOld || id2 == idOld) ? sigma * openFracPos
                                        : sigma * openFracNeg;

}
