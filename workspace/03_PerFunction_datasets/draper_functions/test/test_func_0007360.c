initConstants() {


  yukawa[1][1]  = settingsPtr->parm("LeftRightSymmmetry:coupHee");
  yukawa[2][1]  = settingsPtr->parm("LeftRightSymmmetry:coupHmue");
  yukawa[2][2]  = settingsPtr->parm("LeftRightSymmmetry:coupHmumu");
  yukawa[3][1]  = settingsPtr->parm("LeftRightSymmmetry:coupHtaue");
  yukawa[3][2]  = settingsPtr->parm("LeftRightSymmmetry:coupHtaumu");
  yukawa[3][3]  = settingsPtr->parm("LeftRightSymmmetry:coupHtautau");


  gL            = settingsPtr->parm("LeftRightSymmmetry:gL");
  vL            = settingsPtr->parm("LeftRightSymmmetry:vL");
  mW            = particleDataPtr->m0(24);

}
