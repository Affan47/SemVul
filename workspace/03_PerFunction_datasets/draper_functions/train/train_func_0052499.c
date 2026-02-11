ooCapabilityCheckCompatibility_Simple
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245AudioCapability* audioCap, int dir)
{
   int noofframes=0, cap;

   OOTRACEDBGC2("Comparing channel with codec type: %d\n", audioCap->t);

   switch(audioCap->t)
   {
   case T_H245AudioCapability_g711Ulaw56k:
      cap = OO_G711ULAW56K;
      noofframes = audioCap->u.g711Ulaw56k;
      break;
   case T_H245AudioCapability_g711Ulaw64k:
      cap = OO_G711ULAW64K;
      noofframes = audioCap->u.g711Ulaw64k;
      break;
   case T_H245AudioCapability_g711Alaw64k:
      cap = OO_G711ALAW64K;
      noofframes = audioCap->u.g711Alaw64k;
      break;
   case T_H245AudioCapability_g711Alaw56k:
      cap = OO_G711ALAW56K;
      noofframes = audioCap->u.g711Alaw56k;
      break;


   case T_H245AudioCapability_g728:
      cap = OO_G728;
      noofframes = audioCap->u.g728;
      break;
   case T_H245AudioCapability_g729:
      cap = OO_G729;
      noofframes = audioCap->u.g729;
      break;
   case T_H245AudioCapability_g729AnnexA:
      cap = OO_G729A;
      noofframes = audioCap->u.g729AnnexA;
      break;
   case T_H245AudioCapability_g729wAnnexB:
      cap = OO_G729B;
      noofframes = audioCap->u.g729wAnnexB;
      break;
   case T_H245AudioCapability_g7231:
     cap = OO_G7231;
     noofframes = audioCap->u.g7231->maxAl_sduAudioFrames;
     break;

   default:
      return FALSE;
   }

   OOTRACEDBGC3("Comparing codecs: current=%d, requested=%d\n",
      epCap->cap, cap);
   if(cap != epCap->cap) { return FALSE; }


   if(dir & OORX)
   {
      OOTRACEDBGC3("Comparing RX frame rate: channel's=%d, requested=%d\n",
         ((OOCapParams*)epCap->params)->rxframes, noofframes);
      if(((OOCapParams*)epCap->params)->rxframes >= noofframes) {
         return TRUE;
      }


   }


   if(dir & OOTX)
   {
      OOTRACEDBGC3("Comparing TX frame rate: channel's=%d, requested=%d\n",
         ((OOCapParams*)epCap->params)->txframes, noofframes);
      if(((OOCapParams*)epCap->params)->txframes <= noofframes) {
         return TRUE;
      }


   }
   return FALSE;

}
