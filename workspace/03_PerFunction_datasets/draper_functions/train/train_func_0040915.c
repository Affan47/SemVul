HandleReturnsZero(char *args,char *value,int useshell)

{ char command[CF_BUFSIZE];
  char argv[CF_MAXFARGS][CF_EXPANDSIZE];

if (ACTION != groups)
   {
   yyerror("Use of ReturnsZero(s) outside of class assignment");
   }

FunctionArgs(args,argv,1);

Debug("HandleReturnsZero(%s)\n",argv);

if (*argv[0] == '/')
   {
   strncpy(command,argv[0],CF_BUFSIZE);

   if (ShellCommandReturnsZero(command,useshell))
      {
      strcpy(value,CF_ANYCLASS);
      return;
      }
   }
 else
    {
    yyerror("ExecResult(/command) must specify an absolute path");
    }

 strcpy(value,CF_NOCLASS);
}
