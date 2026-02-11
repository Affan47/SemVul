ParseNonTerminal(s_token *token_p, bool skip)
{
   char *index;
   token_p->tt = T_EXP;
   if (skip==false) {
      token_p->has_patterns=false;
      index = token_p->pattern;
      while (index==token_p->pattern || indexOfTerminal(token_p->s[0])==-1) {
         if (token_p->has_patterns==false && is_pattern(token_p->s[0])) {
            token_p->has_patterns=true;
         }
         switch (token_p->type){
            case TYPE_CSTR:
            case TYPE_HOST:
               index[0]=tolower(token_p->s[0]);
               break;
            default:
               index[0]=token_p->s[0];
         }

         index++;
         token_p->s++;
      }
      index[0]='\0';
   } else {
      while (indexOfTerminal(token_p->s[0])==-1) {
         token_p->s++;
      }
   }
}
