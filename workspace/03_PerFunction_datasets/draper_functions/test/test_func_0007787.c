sort_init() {

   int thread;
   int i, height;
   int pos;


   for (thread = 0; thread < ThreadMax; thread++) {
      for (height = 0; height < HeightMax; height++) {
         for (i = 0; i < KillerNb; i++) Killer[thread][height][i] = MoveNone;
      }
   }


   for (i = 0; i < HistorySize; i++) HistEval[i] = HistoryEvalValue;


   for (i = 0; i < HistorySize; i++) History[i] = 0;

   for (i = 0; i < HistorySize; i++) {
      HistHit[i] = 1;
      HistTot[i] = 1;
   }


   for (pos = 0; pos < CODE_SIZE; pos++) Code[pos] = GEN_ERROR;

   pos = 0;


   PosLegalEvasion = pos;
   Code[pos++] = GEN_LEGAL_EVASION;

   for (thread = 0; thread < SlaveMax; thread++) Code[pos++] = GEN_END;

   PosSEE = pos;
   Code[pos++] = GEN_TRANS;
   Code[pos++] = GEN_CAPTURE;
   Code[pos++] = GEN_KILLER;
   Code[pos++] = GEN_QUIET;
   Code[pos++] = GEN_BAD;

   for (thread = 0; thread < SlaveMax; thread++) Code[pos++] = GEN_END;


   PosEvasionQS = pos;
   Code[pos++] = GEN_EVASION_QS;

   for (thread = 0; thread < SlaveMax; thread++) Code[pos++] = GEN_END;

   PosCheckQS = pos;
   Code[pos++] = GEN_TRANS;
   Code[pos++] = GEN_CAPTURE_QS;
   Code[pos++] = GEN_CHECK_QS;

   for (thread = 0; thread < SlaveMax; thread++) Code[pos++] = GEN_END;

   PosCaptureQS = pos;
   Code[pos++] = GEN_TRANS;
   Code[pos++] = GEN_CAPTURE_QS;

   for (thread = 0; thread < SlaveMax; thread++) Code[pos++] = GEN_END;

   ASSERT(pos<CODE_SIZE);
}
