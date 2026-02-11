HandleFunctionObject(char *fn)

{ char local[CF_BUFSIZE];

Debug("HandleFunctionObject(%s)\n",fn);

if (ACTION == methods)
   {
   strncpy(CURRENTOBJECT,fn,CF_BUFSIZE-1);
   ACTIONPENDING = true;
   return;
   }

if ((ACTION != alerts) && (!IsDefinedClass(CLASSBUFF)))
   {
   Debug("Function object class was beyond current environment (%s)\n",CLASSBUFF);
   return;
   }

if (IsBuiltinFunction(fn))
   {
   local[0] = '\0';
   strcpy(local,EvaluateFunction(fn,local));

   switch (ACTION)
      {
      case groups:
          InstallGroupRValue(local,simple);
          break;

      case control:
          if (strncmp("CF_ASSOCIATIVE_ARRAY",local,strlen("CF_ASSOCIATIVE_ARRAY")) == 0)
             {
             break;
             }

          InstallControlRValue(CURRENTITEM,local);
          break;

      case alerts:

          if (strcmp(local,"noinstall") != 0)
             {
             Debug("Recognized function %s\n",fn);
             strncpy(CURRENTOBJECT,fn,CF_BUFSIZE-1);
             ACTIONPENDING = true;
             }
          else
             {
             Debug("Not recognized %s\n",fn);
             }
          break;

      default: snprintf(OUTPUT,CF_BUFSIZE,"Function call %s out of place",fn);
          yyerror(OUTPUT);
      }
   }
}
