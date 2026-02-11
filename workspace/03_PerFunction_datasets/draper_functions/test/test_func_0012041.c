InsertInRTPQ(RtpData *pRtpData,int MaxNetQueueLen)
{
   RtpData *pLast = pRtpQueue;
   u_int16 Seq = pRtpData->pData->seq;

   if(pLast == NULL) {

      pLast = (RtpData *) &pRtpQueue;
      SLOG(("%s: Adding %d to empty Queue\n",__FUNCTION__,Seq));
   }
   else {
      RtpData *p = pLast->Link;

      if(p == NULL) {

         if(Seq == pLast->pData->seq) {
            SLOG(("%s#%d: tossing duplicate %d\n",__FUNCTION__,__LINE__,Seq));
            DuplicatePackets++;
            free(pRtpData->pData);
            free(pRtpData);
            pLast = NULL;
         }
         else if(Between(Seq,pLast->pData->seq,pLast->pData->seq + MaxNetQueueLen)) {

            SLOG(("%s: inserted %d before %d\n",Seq,pLast->pData->seq));
            D2PRINTF(("\ns(%d,%d)",pLast->pData->seq,Seq));
            OutofSeqPackets++;
            pRtpData->Link = pRtpQueue;
            pLast = (RtpData *) &pRtpQueue;
         }
      }
      else  {
         while(p != NULL) {
            if(Seq == pLast->pData->seq || Seq == p->pData->seq) {
               SLOG(("%s#%d: tossing duplicate %d\n",__FUNCTION__,__LINE__,Seq));
               DuplicatePackets++;
               free(pRtpData->pData);
               free(pRtpData);
               pLast = NULL;
               break;
            }
            else if(Between(pLast->pData->seq,Seq,p->pData->seq)) {

               pRtpData->Link = p;
               OutofSeqPackets++;
               SLOG(("%s: inserting %d between %d and %d\n",__FUNCTION__,
                     pLast->pData->seq,Seq,p->pData->seq));
               D2PRINTF(("\ns(%d,%d,%d)",pLast->pData->seq,Seq,p->pData->seq));
               break;
            }
            pLast = p;
            p = p->Link;
         }
      }

      if(pLast != NULL) {
         SLOG(("%s: Inserted %d, RtpQCount %d\n",__FUNCTION__,Seq,RtpQCount));
      }
   }

   if(pLast != NULL) {
      D2PRINTF(("q"));
      pLast->Link = pRtpData;
      RtpQCount++;
   }
}
