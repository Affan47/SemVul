boostAndVertex( bool toLab, bool setVertex) {


  if (toLab) {
    if      (boostType == 2) process.bst(0., 0., betaZ, gammaZ);
    else if (boostType == 3) process.rotbst(MfromCM);


    if (event.size() > 0) {
      if      (boostType == 2) event.bst(0., 0., betaZ, gammaZ);
      else if (boostType == 3) event.rotbst(MfromCM);
    }


  } else {
    if      (boostType == 2) process.bst(0., 0., -betaZ, gammaZ);
    else if (boostType == 3) process.rotbst(MtoCM);


    if (event.size() > 0) {
      if      (boostType == 2) event.bst(0., 0., -betaZ, gammaZ);
      else if (boostType == 3) event.rotbst(MtoCM);
    }
  }


  if (setVertex && doVertexSpread) {
    Vec4 vertex = beamShapePtr->vertex();
    for (int i = 0; i < process.size(); ++i) process[i].vProd( vertex);
    for (int i = 0; i < event.size(); ++i) event[i].vProd( vertex);
  }

}
