AuditStatusMessage(FILE *fp,char status)

{
switch (status)
   {
   case CF_CHG:
       fprintf(fp,"made a system correction");
       break;

   case CF_WARN:
       fprintf(fp,"promise not kept, no action taken");
       break;

   case CF_TIMEX:
       fprintf(fp,"timed out");
       break;

   case CF_FAIL:
       fprintf(fp,"failed to make a correction");
       break;

   case CF_DENIED:
       fprintf(fp,"was denied access to an essential resource");
       break;

   case CF_INTERPT:
       fprintf(fp,"was interrupted\n");
       break;

   case CF_NOP:
       fprintf(fp,"was applied but performed no required actions");
       break;

   case CF_UNKNOWN:
       fprintf(fp,"was applied but status unknown");
       break;

   case CF_REPORT:
       fprintf(fp,"report");
       break;
   }

}
