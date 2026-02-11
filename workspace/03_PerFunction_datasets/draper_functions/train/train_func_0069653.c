amdmsFreeParticleEventSetup(amdmsPARTICLE_EVENT_SETUP *setup)
{
   int i;
   if (setup == NULL) {
      return amdmsFAILURE;
   }

   if (setup->pes != NULL) {
      for(i=0; i<setup->nPE; i++){
         free(setup->pes[i].values);
      }
   }
   setup->peFlag = amdmsFALSE;
   setup->peLimit = 0.0;
   setup->nPE = 0;
   setup->nSPE = 0;
   if (setup->pes != NULL) {
      free(setup->pes);
      setup->pes = NULL;
   }
   return amdmsSUCCESS;
}
