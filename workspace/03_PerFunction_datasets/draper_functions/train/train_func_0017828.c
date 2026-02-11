DecompressRTP()
{
   RtpData *pRtp = pRtpQueue;
   RtpData *pNext;
   gsm_byte *pGSM;
   int DataLen;
   char *dp;
   struct adpcm_state adpcm;
   u_int8 *sp;

   while(pRtp != NULL && NextSeq == pRtp->pData->seq) {
      NextSeq++;
      pRtpQueue = pRtp->Link;
      RtpQCount--;
      SLOG(("%s: Decompressing %d\n",__FUNCTION__,pRtp->pData->seq));
      switch(pRtp->pData->pt) {
         case RTP_PT_PCMU:
            dp = (char *) pRtp->pData + RTP_HDR_SIZE;
            DataLen = pRtp->Len - RTP_HDR_SIZE;
            DecompressULaw(dp,DataLen);
            break;

         case RTP_PT_GSM:
            if(gsmh == NULL) {
               gsmh = gsm_create();
            }
            pGSM = (gsm_byte *) pRtp->pData + RTP_HDR_SIZE;
            DataLen = pRtp->Len - RTP_HDR_SIZE;
            DecompressGSM(pGSM,DataLen,gsmh);
            break;

         case RTP_PT_DVI4_8K:
            sp = (u_int8 *) pRtp->pData + RTP_HDR_SIZE;
            dp = (char *) sp  + 4;
            DataLen = pRtp->Len - RTP_HDR_SIZE - 4;
            adpcm.valprev = (sp[0] << 8) | sp[1];
            adpcm.index = sp[2];
            DecompressADPCM(dp,DataLen,&adpcm);
            break;

         case RTP_PT_G726:
            if(g726h == NULL) {
               g726h = g726_init(NULL,32000,G726_ENCODING_LINEAR,
                                 G726_PACKING_RIGHT);
            }
            sp = (uint8_t *) pRtp->pData + RTP_HDR_SIZE;
            DataLen = pRtp->Len - RTP_HDR_SIZE;
            DecompressG726(sp,DataLen);
            break;

         default:
            break;
      }

      pNext = pRtp->Link;
      free(pRtp->pData);
      free(pRtp);
      pRtp = pNext;
   }
}
