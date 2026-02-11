parse_expression_sequence( LEXCONTEXT *pc, DBUF *parent,  char *end_of_expression )
{
  STRING_PART *part;
  int c;
  YYLTYPE start;
  char *eof;
#ifdef IS_REENTRANT
  yyscan_t yyscanner = pc->yyscanner;
  struct yyguts_t * yyg = (struct yyguts_t*) yyscanner;
#endif
  int countb = 0;


  start.file_id = yyloc.file_id;
  start.first_line = start.last_line = yylineno;
  start.first_column = start.last_column = yycolumn;

  part = STRING_PART_init( 1, &start );
  if (!part) {
    return 0;
  }

  while ( (c =  MY_YY_INPUT) != -1) {

    if (parent) {
      DBUF_add( parent, &c, sizeof(char) );
    }

    DBUF_add(  &part->part_data, &c, sizeof(char) );

    if (c == '[') {
      countb ++;
      continue;
    }
    if (c == ']') {
      if (countb > 0) {
        countb --;
        continue;
      }
    }

    if (c == '\'' || c == '"') {
	do_parse_string( pc, &part->part_data, c );
    }

    eof = (char *) dbuf_ends_with( &part->part_data, end_of_expression );
    if (eof) {
      *eof = '\0';
      break;
    }
  }

  if (c == -1) {
     do_yyerror ( &start, (PARSECONTEXT *) pc,  "The string constant is not closed, it goes on and on until the end of the file" );
     return  0;
  }


  return part;
}
