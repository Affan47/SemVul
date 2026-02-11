get_cwd
(  void
)
   {  char buf[MY_PATH_MAX+1]
   ;  mcxTing* ret = NULL
   ;  if (use_cwd)
      {  if (!getcwd(buf, MY_PATH_MAX + 1))
         mcxErr(us, "cannot get current directory")
      ;  else
         ret = mcxTingNew(buf)
   ;  }
      else
      {  mcxIO* xfpipe = mcxIOnew("dummy-file-name", "r")
      ;  FILE*  p =  popen("pwd", "r")
      ;  if (p)
         {  mcxTing *pwd = mcxTingEmpty(NULL, 256)
         ;  xfpipe->fp = p
         ;  mcxIOreadLine(xfpipe, pwd, MCX_READLINE_CHOMP)


         ;  if (!ferror(p))
            {  pclose(p)
            ;  xfpipe->fp = NULL
            ;  mcxIOfree(&xfpipe)
            ;  ret = pwd
         ;  }
            else
            mcxErr(us, "pwd does not want to play")
      ;  }
         else
         mcxErr(us, "cannot execute pwd")
   ;  }
      return ret
;  }
