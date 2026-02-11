caps(char *text) {
   int i;
   if (text)
      for (i=0; i<sstrlen(text); i++)
          if ( text[i] >= 'a' && text[i] <= 'z' )
             text[i] = text[i]-32;
   return text;
   }
