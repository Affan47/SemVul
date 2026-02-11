errPrint (ASN1ErrInfo* pErrInfo)
{
   char lbuf[200];
   printf ("ASN.1 ERROR: Status %d\n", pErrInfo->status);
   printf ("%s\n", errFmtMsg (pErrInfo, lbuf));
   printf ("Stack trace:");
   while (pErrInfo->stkx > 0) {
      pErrInfo->stkx--;
      printf ("  Module: %s, Line %d\n",
              pErrInfo->stack[pErrInfo->stkx].module,
              pErrInfo->stack[pErrInfo->stkx].lineno);
   }
   errFreeParms (pErrInfo);
}
