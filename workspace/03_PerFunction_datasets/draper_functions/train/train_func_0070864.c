HandleOptionalMountablesAttribute(char *item)

{ char value[CF_MAXVARSIZE],ebuff[CF_EXPANDSIZE];

value[0] = '\0';
ExpandVarstring(item,ebuff,NULL);
sscanf(ebuff,"%*[^=]=%s",value);

if (value[0] == '\0')
   {
   yyerror("mount attribute with no value");
   }

Debug1("HandleOptionalMountItem(%s)\n",value);

switch(GetCommAttribute(item))
   {
   case cfmountoptions:
      strcpy(MOUNTOPTS, value);
      break;

   case cfreadonly:
       if ((strcmp(value,"on")==0) || (strcmp(value,"true")==0))
          {
          CF_MOUNT_RO=true;
          }
       break;

   default:         yyerror("Illegal mount option"
                            "(mountoptions/readonly)");
   }
}
