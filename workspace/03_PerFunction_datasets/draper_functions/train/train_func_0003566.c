blinkTimeOut(void)
{
  if (blinkPhase()==Normal)
   {
     const MSBinaryMatrix& blinkM=currentBlinkMatrix();
     if (verify(blinkM)==MSTrue)
      {
	MSBoolean stopTimer=(drawBlink(blinkM,Reverse)==MSTrue)?MSFalse:MSTrue;
	blinkMatrix(blinkM);
	toggleBlinkPhase();
	if (stopTimer==MSTrue) stopBlinkTimer();
      }
   }
  else
   {
     (void)drawBlink(currentBlinkMatrix(),Normal);
     toggleBlinkPhase();
   }
}
