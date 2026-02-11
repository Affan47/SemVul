parse_close(parse_t * parse) {

   int i;

   ASSERT(parse_is_ok(parse));

   parse->string = NULL;
   parse->pos = 0;

   for (i = 0; i < parse->keyword_nb; i++) {
      my_string_clear(&parse->keyword[i]);
   }

   parse->keyword_nb = 0;
}
