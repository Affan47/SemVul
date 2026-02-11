CatchDATE(int act)
{
   if(!fileset_for_info)
      return;

   FileInfo *fi=fileset_for_info->curr();
   if(!fi)
      return;

   if(is2XX(act))
   {
      if(line.length()>4 && is_ascii_digit(line[4]))
	 fi->SetDate(ConvertFtpDate(line+4),0);
   }
   else	if(is5XX(act))
   {
      if(cmd_unsupported(act))
	 conn->mdtm_supported=false;
   }
   else
   {
      Disconnect();
      return;
   }

   fi->NoNeed(fi->DATE);
   if(!(fi->need&fi->SIZE))
      fileset_for_info->next();

   TrySuccess();
}
