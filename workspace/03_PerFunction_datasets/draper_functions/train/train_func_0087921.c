inc_cmd(cmds, name)
                    struct Execution_Command **cmds;
                    char *name;
{
  int cnt = 0;
  struct Execution_Command *cmd, *ec;

  for (ec = cmd = *cmds; cmd != NULL; ec= cmd, cmd= cmd->next, cnt++)
      if ( (0 == strcmp(cmd->Commandname, name)) ||
           (0 == strcmp(cmd->Commandname, "Misc.")) )
         break;
  if (cmd == NULL)
  {
     cmd= (struct Execution_Command *)getmem(sizeof(*cmd));
     if (cnt <= MAXCOLS-1)
     {
        strcpy(cmd->Commandname, name);
        if (*cmds == NULL)
           ec = *cmds = cmd;
        else
           ec->next= cmd;
     }
     else
     {
        strcpy(ec->Commandname, "Misc.");
        cmd = ec;
     }
  }
  cmd->count++;
}
