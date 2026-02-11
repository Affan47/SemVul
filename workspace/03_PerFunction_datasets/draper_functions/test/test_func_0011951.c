findReplacement(int cols, EndNode *n, double table[][cols], wchar_t *string, int i, int j, double value){
  wchar_t *repl;
  int c;

  while(n != NULL){
     repl = n->edit;
     c = 0;

     while(1){
        if(string[c] == repl[c] || repl[c] == L'\0'){
            if(repl[c] == '\0'){

                 addValueToTable(cols, table, i, (j + c), (value + n->value));
                 goto nextRepl;
            }
            c++;
        }
        else break;
     }
     nextRepl: n = n->nextEN;
  }
  return 0;
}
