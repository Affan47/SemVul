fix_str(char* str,int len,char endChar)
{
   int oldLen;

   if ( endChar == '\0' )
      oldLen = strlen(str);
   else
   {
      oldLen = Misc::str_chr(str,endChar)-1;
      err_if ( oldLen == -1 )
         err_now("Misc::fix_str");
   }

   if ( len > oldLen )
      memset( str+oldLen, ' ', len-oldLen );

   str[len] = '\0';
}
