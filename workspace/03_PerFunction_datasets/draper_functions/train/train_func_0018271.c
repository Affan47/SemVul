yybegin (const char *fname)
{
  yyin = fopen (fname, "r");
  if (yyin == NULL)
    {
      perror (fname);
      exit (1);
    }
  lexer_line.file = input_file_by_name (fname);
  lexer_line.line = 1;
}
