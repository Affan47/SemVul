reset(void)
{
  resetOdometer();
  myInterpolation.reset();
  myEncoderInterpolation.reset();
  if (myOrigRobotConfig != NULL)
    delete myOrigRobotConfig;
  myOrigRobotConfig = new ArRobotConfigPacketReader(this, true);
  myFirstEncoderPose = true;


  myTransVelMax = 0;
  myTransAccel = 0;
  myTransDecel = 0;
  myRotVelMax = 0;
  myRotAccel = 0;
  myRotDecel = 0;

  myRobotLengthFront = 0;
  myRobotLengthRear = 0;

  myLeftVel = 0;
  myRightVel = 0;
  myBatteryVoltage = 13;
  myBatteryAverager.clear();
  myBatteryAverager.add(myBatteryVoltage);
  myStallValue = 0;
  myControl = 0;
  myFlags = 0;
  myFaultFlags = 0;
  myHasFaultFlags = 0;
  myCompass = 0;
  myAnalogPortSelected = 0;
  myAnalog = 0;
  myDigIn = 0;
  myDigOut = 0;
  myIOAnalogSize = 0;
  myIODigInSize = 0;
  myIODigOutSize = 0;
  myLastIOPacketReceivedTime.setSec(0);
  myLastIOPacketReceivedTime.setMSec(0);
  myVel = 0;
  myRotVel = 0;
  myChargeState = CHARGING_UNKNOWN;
  myLastX = 0;
  myLastY = 0;
  myLastTh = 0;
  mySentPulse = false;
  myIsConnected = false;
  myIsStabilizing = false;

  myTransVal = 0;
  myTransVal2 = 0;
  myTransType = TRANS_NONE;
  myLastTransVal = 0;
  myLastTransVal2 = 0;
  myLastTransType = TRANS_NONE;
  myLastTransSent.setToNow();
  myActionTransSet = false;
  myLastActionRotStopped = false;
  myLastActionRotHeading = false;

  myRotVal = 0;
  myLastRotVal = 0;
  myRotType = ROT_NONE;
  myLastRotType = ROT_NONE;
  myLastRotSent.setToNow();
  myActionRotSet = false;

  myLastPulseSent.setToNow();

  myDirectPrecedenceTime = 0;
  myStateReflectionRefreshTime = 500;

  myActionDesired.reset();

  myMotorPacCurrentCount = 0;
  myMotorPacCount = 0;
  myTimeLastMotorPacket = 0;

  mySonarPacCurrentCount = 0;
  mySonarPacCount = 0;
  myTimeLastSonarPacket = 0;

  myLeftEncoder = 0;
  myRightEncoder = 0;

  myWarnedAboutExtraSonar = false;
  myOdometryDelay = 0;
}
