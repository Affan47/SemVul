cmListFileLexerSetToken(cmListFileLexer* lexer, const char* text,
                                    int length)
{

  lexer->token.line = lexer->line;
  lexer->token.column = lexer->column;


  if(lexer->token.text)
    {
    if(text && length < lexer->size)
      {
      strcpy(lexer->token.text, text);
      lexer->token.length = length;
      return;
      }
    free(lexer->token.text);
    lexer->token.text = 0;
    lexer->size = 0;
    }


  if(text)
    {
    lexer->token.text = strdup(text);
    lexer->token.length = length;
    lexer->size = length+1;
    }
  else
    {
    lexer->token.length = 0;
    }
}
