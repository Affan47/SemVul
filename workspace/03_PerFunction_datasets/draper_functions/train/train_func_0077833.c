HandleOptionalDirAttribute(char *item)

{ char value[CF_MAXVARSIZE],ebuff[CF_EXPANDSIZE];

value[0] = '\0';

ExpandVarstring(item,ebuff,NULL);

sscanf(item,"%*[^=]=%s",value);

if (value[0] == '\0')
   {
   yyerror("Directory attribute with no value");
   }

Debug1("HandleOptionalDirAttribute(%s)\n",value);

switch(GetCommAttribute(item))
   {
   case cfmode:    ParseModeString(value,&PLUSMASK,&MINUSMASK);
                   break;
   case cfflags:   ParseFlagString(value,&PLUSFLAG,&MINUSFLAG);
                   break;
   case cfowner:   strcpy(VUIDNAME,value);
                   break;
   case cfgroup:   strcpy(VGIDNAME,value);
                   break;
   case cfdefine:  HandleDefine(value);
                   break;
   case cfelsedef: HandleElseDefine(value);
                   break;
   case cfsetlog:  HandleCharSwitch("log",value,&LOGP);
                   break;
   case cfsetinform: HandleCharSwitch("inform",value,&INFORMP);
                   break;
   case cfsetaudit: HandleCharSwitch("audit",value,&AUDITP);
                   break;
   case cfifelap:  HandleIntSwitch("ifelapsed",value,&PIFELAPSED,0,999999);
                   break;
   case cfexpaft:  HandleIntSwitch("expireafter",value,&PEXPIREAFTER,0,999999);
                   break;
   case cfrxdirs:  HandleCharSwitch("rxdirs",value,&RXDIRS);
                   break;

   default:        yyerror("Illegal directory attribute");
   }
}
