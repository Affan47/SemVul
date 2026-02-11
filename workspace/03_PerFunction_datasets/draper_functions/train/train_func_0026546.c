EvaluateORString(char *class,struct Item *list,int fromIsInstallable)

{ char *sp, cbuff[CF_BUFSIZE];
  int result = false;

if (class == NULL)
   {
   return false;
   }

Debug4("\n--------\nEvaluateORString(%s)\n",class);

for (sp = class; *sp != '\0'; sp++)
   {
   while (*sp == '|')
      {
      sp++;
      }

   memset(cbuff,0,CF_BUFSIZE);

   sp += GetORAtom(sp,cbuff);

   if (strlen(cbuff) == 0)
      {
      break;
      }


   if (IsBracketed(cbuff))
      {
      cbuff[strlen(cbuff)-1] = '\0';

      result |= EvaluateORString(cbuff+1,list,fromIsInstallable);
      Debug4("EvalORString-temp-result-y=%d (%s)\n",result,cbuff+1);
      }
   else
      {
      result |= EvaluateANDString(cbuff,list,fromIsInstallable);
      Debug4("EvalORString-temp-result-n=%d (%s)\n",result,cbuff);
      }

   if (*sp == '\0')
      {
      break;
      }
   }

Debug4("EvaluateORString(%s) returns %d\n",class,result);
return result;
}
