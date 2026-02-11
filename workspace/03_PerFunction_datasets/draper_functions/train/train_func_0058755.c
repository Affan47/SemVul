readLine(char *line){
   int pos;
   Number *n1;
   struct lconv *locale;

   locale = localeconv();

   if((*line != '"' && *line != '\'') && (isDigitBase(*line) || *line == '-' || *line == '+' || *line == *(locale->decimal_point))){


      if(NULL == (n1 = readNumber(line, &pos))){
	 setStringError("Error: Cannot read number.");
         return;
      }

      SaveStackState(0);
      Push(n1);
      UndoStackState(1);


      if(strlen(line) > pos) runCmd(line+pos);

   } else {


      runCmd(line);
   }
}
