HandleOptionalInterface(char *item)

{ char value[CF_MAXVARSIZE],ebuff[CF_EXPANDSIZE];

value[0] = '\0';

ExpandVarstring(item,ebuff,NULL);

sscanf(ebuff,"%*[^=]=%s",value);

if (value[0] == '\0')
   {
   yyerror("intefaces attribute with no value");
   }

Debug1("HandleOptionalInterfaceAttribute(value=%s)\n",value);

switch(GetCommAttribute(item))
   {
   case cfsetnetmask:   HandleNetmask(value);
                        break;
   case cfsetbroadcast: HandleBroadcast(value);
                        break;
   case cfsetipaddress: HandleIPAddress(value);
                        break;

   default:        yyerror("Illegal interfaces attribute");
   }

}
