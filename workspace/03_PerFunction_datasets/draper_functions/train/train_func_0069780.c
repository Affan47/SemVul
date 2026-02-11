parse_id(uci_t * uci, const char string[]) {

   parse_t parse[1];
   char command[StringSize];
   char option[StringSize];
   char argument[StringSize];

   ASSERT(uci!=NULL);
   ASSERT(string!=NULL);


   strcpy(command,"id");

   parse_open(parse,string);
   parse_add_keyword(parse,"author");
   parse_add_keyword(parse,"name");


   while (parse_get_word(parse,option,StringSize)) {

      parse_get_string(parse,argument,StringSize);
      if (UseDebug) my_log("POLYGLOT COMMAND \"%s\" OPTION \"%s\" ARGUMENT \"%s\"\n",command,option,argument);

      if (false) {
      } else if (my_string_equal(option,"author")) {
         ASSERT(!my_string_empty(argument));
         my_string_set(&uci->author,argument);
      } else if (my_string_equal(option,"name")) {
         ASSERT(!my_string_empty(argument));
         my_string_set(&uci->name,argument);
      } else {
         my_log("POLYGLOT unknown option \"%s\" for command \"%s\"\n",option,command);
      }
   }

   parse_close(parse);

   if (UseDebug) my_log("POLYGLOT engine name \"%s\" author \"%s\"\n",uci->name,uci->author);
}
