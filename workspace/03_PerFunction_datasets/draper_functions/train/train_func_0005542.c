ParseFile()
{

  if(!cmListFileLexer_SetFileName(this->Lexer, this->FileName))
    {
    cmSystemTools::Error("cmListFileCache: error can not open file ",
                         this->FileName);
    return false;
    }


  bool haveNewline = true;
  while(cmListFileLexer_Token* token =
        cmListFileLexer_Scan(this->Lexer))
    {
    if(token->type == cmListFileLexer_Token_Space)
      {
      }
    else if(token->type == cmListFileLexer_Token_Newline)
      {
      haveNewline = true;
      }
    else if(token->type == cmListFileLexer_Token_Identifier)
      {
      if(haveNewline)
        {
        haveNewline = false;
        if(this->ParseFunction(token->text, token->line))
          {
          this->ListFile->Functions.push_back(this->Function);
          }
        else
          {
          return false;
          }
        }
      else
        {
        cmOStringStream error;
        error << "Error in cmake code at\n"
              << this->FileName << ":" << token->line << ":\n"
              << "Parse error.  Expected a newline, got "
              << cmListFileLexer_GetTypeAsString(this->Lexer, token->type)
              << " with text \"" << token->text << "\".";
        cmSystemTools::Error(error.str().c_str());
        return false;
        }
      }
    else
      {
      cmOStringStream error;
      error << "Error in cmake code at\n"
            << this->FileName << ":" << token->line << ":\n"
            << "Parse error.  Expected a command name, got "
            << cmListFileLexer_GetTypeAsString(this->Lexer, token->type)
            << " with text \""
            << token->text << "\".";
      cmSystemTools::Error(error.str().c_str());
      return false;
      }
    }
  return true;
}
