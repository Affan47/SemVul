AbortTransfer(int sd,char *sendbuffer,char *filename)

{
CfOut(cf_verbose,"","Aborting transfer of file due to source changes\n");

snprintf(sendbuffer,CF_BUFSIZE,"%s%s: %s",CF_CHANGEDSTR1,CF_CHANGEDSTR2,filename);

if (SendTransaction(sd,sendbuffer,0,CF_DONE) == -1)
   {
   CfOut(cf_verbose,"send","Send failed in GetFile");
   }
}
