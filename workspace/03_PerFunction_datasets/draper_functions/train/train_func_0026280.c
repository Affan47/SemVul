LevelOneFrame(float frameInBuffer)
{
   float  curFrame;
   float  fabsCurFrame;
   float  curSign;

   curFrame = frameInBuffer;
   if (curFrame < 0.0) {
      curSign = -1.0;
   }
   else {
      curSign = 1.0;
   }
   fabsCurFrame = (float)fabs(curFrame);
   mFrameSum += fabsCurFrame;

   for (int f = 0; f < LEVELER_FACTORS; ++f) {
     if (fabsCurFrame <= gLimit[f]) {
        curFrame *= (float)gAdjFactor[f];
        curFrame += (float)(gAddOnValue[f] * curSign);
        return curFrame;
     }
   }
   return (float)0.99;
}
