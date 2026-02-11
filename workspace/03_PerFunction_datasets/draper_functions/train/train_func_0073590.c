testsDiscard(
   H_COLLECT * h_ctxt)
{
   onlineTests *context = (onlineTests *) h_ctxt->havege_tests;
   procShared  *tps = TESTS_SHARED(h_ctxt);
   procInst    *p;
   H_UINT      i;

   if (0==tps->testsUsed)
      return 0;
   if (context->result!=0)
      return -1;
   p = tps->runTests + context->runIdx;
   switch(p->action) {
      case A_RUN:
         if (0 != context->pA->procRetry)
            return 1;
         for (i = 0;i<context->pA->testRun;i++)
            if (0 !=(context->pA->results[i].testResult & 1))
               return 1;
         break;
      case B_RUN:
         if (0 != context->pB->procRetry)
            return 1;
         for (i=0;i<context->pB->testNbr;i++)
            if (0!=(context->pB->results[i].testResult & 0xff))
               return 1;
         break;
      }
   return 0;
}
