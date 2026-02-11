StringHTMLEncode (char* string, GRSThttpBody *bp){

  char* current_char;
  char* tmp;
  int n;
  tmp=malloc(2);

  *(tmp+1)='\0';
  current_char=string;
  while(*current_char != '\0'){

    if  (*current_char  == '<')     GRSThttpPrintf (bp,"&lt;");
    else if (*current_char == '>')  GRSThttpPrintf (bp,"&gt;");
    else if (*current_char == '&')  GRSThttpPrintf (bp,"&amp;");
    else if (*current_char == '\'') GRSThttpPrintf (bp,"&apos;");
    else if (*current_char == '"')  GRSThttpPrintf (bp,"&quot;");
    else{
       *tmp=*current_char;
       GRSThttpPrintf(bp, "%s", tmp);

    }
    current_char++;
  }
  return;
}
