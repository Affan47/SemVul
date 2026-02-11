HasBrackets(char *s,struct Promise *pp)


{ int i, level= 0, yes = 0;

for (i = 0; i < strlen(s); i++)
   {
   if (s[i] == '(')
      {
      yes++;
      level++;
      if (i > 0 && !strchr(".&|!(", s[i+1]))
         {
         CfOut(cf_error,""," !! Class expression \"%s\" has a missing operator in front of '('",s);
         }
      }

   if (s[i] == ')')
      {
      level--;
      if (i < strlen(s)-1 && !strchr(".&|!)", s[i+1]))
         {
         CfOut(cf_error,""," !! Class expression \"%s\" has a missing operator after ')'",s);
         }
      }
   }

if (level != 0)
   {
   CfOut(cf_error,""," !! Class expression \"%s\" has unbalanced brackets",s);
   PromiseRef(cf_error,pp);
   return true;
   }

if (yes > 1)
   {
   CfOut(cf_error,""," !! Class expression \"%s\" has multiple brackets",s);
   PromiseRef(cf_error,pp);
   }
else if (yes)
   {
   return true;
   }

return false;
}
