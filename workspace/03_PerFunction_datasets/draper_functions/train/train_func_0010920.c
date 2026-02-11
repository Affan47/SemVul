kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
{
  int i;
  if(!cp)
    {
    return 0;
    }
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    char** c = cp->Commands[i];
    while(*c)
      {
      free(*c++);
      }
    free(cp->Commands[i]);
    }
  cp->NumberOfCommands = 0;
  if(cp->Commands)
    {
    free(cp->Commands);
    cp->Commands = 0;
    }
  if(command)
    {
    return kwsysProcess_AddCommand(cp, command);
    }
  return 1;
}
