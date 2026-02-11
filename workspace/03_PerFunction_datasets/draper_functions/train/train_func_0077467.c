do_preproc()
{
   int val, no_match=0;

   if( (val=get_onetok(SKIP_SPACE)) == TK_WORD )
   {
      if( strcmp(curword, "ifdef") == 0 )
         do_proc_if(0);
      else if( strcmp(curword, "ifndef") == 0 )
         do_proc_if(1);
      else if( strcmp(curword, "if") == 0 )
         do_proc_if(2);
      else if( strcmp(curword, "elif") == 0 )
         do_proc_if(3);
      else if( strcmp(curword, "else") == 0 )
         do_proc_else();
      else if( strcmp(curword, "endif") == 0 )
         do_proc_endif();
      else if(if_false)
         no_match=1;
      else
      {
         if( strcmp(curword, "include") == 0 )
            do_proc_include();
         else if( strcmp(curword, "define") == 0 )
            do_proc_define();
         else if( strcmp(curword, "undef") == 0 )
            do_proc_undef();
         else if( strcmp(curword, "error") == 0 ) {
	    strcpy(curword, "#error");
            do_proc_copy_hashline(); pgetc();
	    cerror(curword);
	 } else if( strcmp(curword, "warning") == 0 ) {
	    strcpy(curword, "#warning");
            do_proc_copy_hashline(); pgetc();
	    cwarn(curword);
	 } else if( strcmp(curword, "pragma") == 0 ) {
            do_proc_copy_hashline(); pgetc();

	 } else if( strcmp(curword, "line") == 0 ) {
            do_proc_copy_hashline(); pgetc();

	 } else if( strcmp(curword, "asm") == 0 ) {
	    alltok |= 0x100;
            return do_proc_copy_hashline();
	 } else if( strcmp(curword, "endasm") == 0 ) {
	    alltok &= ~0x100;
            return do_proc_copy_hashline();
	 } else
	    no_match=1;
      }
   }
   else no_match=1;

   if( no_match )
   {
      if(!if_false) cerror("Unknown preprocessor directive");
      while( val != '\n' ) val = pgetc();
   }

   *curword = 0;
   return 0;
}
