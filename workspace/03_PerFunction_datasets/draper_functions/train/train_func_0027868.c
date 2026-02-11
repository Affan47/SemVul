cmListFileLexer_Scan(cmListFileLexer* lexer)
{
  if(!lexer->file)
    {
    return 0;
    }
  if(cmListFileLexer_yylex(lexer->scanner, lexer))
    {
    return &lexer->token;
    }
  else
    {
    cmListFileLexer_SetFileName(lexer, 0);
    return 0;
    }
}
