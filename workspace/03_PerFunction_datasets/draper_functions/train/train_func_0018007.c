getCmd(void)
{
    static HE_CMD *cmdList;
    HE_CMD     *cmd;
    HE_CMD     *cmdTail;

    if (!cmdList)
        cmdList = parse();
    if (!cmdList)
        return NULL;

    cmd = cmdList;
    if (cmdList)
        cmdList = cmdList->next;
    cmd->next = (HE_CMD *) NULL;


    if (cmd && ((cmd->func == (HE_FUNC) HEif) ||
                (cmd->func == (HE_FUNC) HEselect)) &&
        !((cmd->argc > 1) && (cmd->argv[1][0] == '-') &&
          (findOpt(cmd->argv[1] + 1) == HE_HELP)))
      {
          he_nestLevel++;

          cmd->sub = getCmd();
          for (cmdTail = cmd->sub;
               cmdTail && HDstrcmp(cmdTail->argv[0], "end");
               cmdTail = cmdTail->next)
              cmdTail->next = getCmd();

          he_nestLevel--;
      }
    return cmd;
}
