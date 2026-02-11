CleanupFFT()
{
   int h;
   for(h=0; (h<MAX_HFFT); h++) {
      if((nFFTLockCount[h] <= 0) && (hFFTArray[h] != NULL)) {
         EndFFT(hFFTArray[h]);
         hFFTArray[h] = NULL;
      }
   }
}
