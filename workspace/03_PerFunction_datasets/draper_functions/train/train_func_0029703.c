StopTalking()
{
   RtpData *pRtp;
   u_int16 NextSeqAvailable;

   if(pRtpQueue != NULL) {

      while((pRtp = pRtpQueue) != NULL) {

         NextSeqAvailable = pRtp->pData->seq;
         while(NextSeq != NextSeqAvailable) {
            SLOG(("%s: Skipping missed seq %d\n",__FUNCTION__,NextSeq));
            D2PRINTF(("m1 %d",NextSeq));
            NextSeq++;
            MissedPackets++;
         }
         D2PRINTF(("\n"));

         DecompressAudio();
      }
   }


   bRxIdle = TRUE;
   bRxBuffering = bRxActive = FALSE;
}
