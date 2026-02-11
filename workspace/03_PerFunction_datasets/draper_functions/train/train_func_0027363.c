printToPrinter(const MSString& printerCmd_,
                                                             const MSIndexVector& pageIndex_)
{
  FILE *fp;
  fp=popen((char *)printerCmd_.string(),"w");
  if(fp==0) return BadFile;
  printPages(fp,pageIndex_);
  if(printPipeBroken==MSTrue)
   {
     printPipeBroken=MSFalse;
     return BadFile;
   }
  else
   {
     pclose(fp);
   }

  return NoError;
}
