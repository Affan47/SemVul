TwoBufferProcessPass1(float *buffer1, sampleCount len1, float *buffer2, sampleCount len2)
{
   int i;


   if((len1 > mFollowLen) || (len2 > mFollowLen))
      return false;


   if (buffer1 == NULL) {


      mLastLevel = mThreshold;
      for(i=0; i<len2; i++) {
         if(mLastLevel < fabs(buffer2[i]))
            mLastLevel = fabs(buffer2[i]);
      }
   }


   if(buffer2 != NULL) {
      Follow(buffer2, mFollow2, len2, mFollow1, len1);
   }

   if(buffer1 != NULL) {
      for (i = 0; i < len1; i++) {
         buffer1[i] = DoCompression(buffer1[i], mFollow1[i]);
      }
   }


#if 0

   memcpy(buffer1, mFollow1, len1*sizeof(float));
#endif


   float *tmpfloat = mFollow1;
   mFollow1 = mFollow2;
   mFollow2 = tmpfloat;

   return true;
}
