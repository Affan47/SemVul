cmDependsFortranParser_Input(cmDependsFortranParser* parser,
                                 char* buffer, size_t bufferSize)
{


  if(!parser->FileStack.empty())
    {
    FILE* file = parser->FileStack.top().File;
    return (int)fread(buffer, 1, bufferSize, file);
    }
  return 0;
}
