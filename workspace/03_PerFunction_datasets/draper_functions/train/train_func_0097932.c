cmdLoop(void)
{
    HE_CMD     *cmd;

    for (cmd = getCmd(); cmd; cmd = getCmd())
      {
          if (cmd->func)
              he_status = (*cmd->func) (cmd);
          else
            {
                fprintf(stderr, "Unknown command: %s.\n", cmd->argv[0]);
                he_status = HE_FAIL;
            }
          deleteCmd(cmd);
      }
}
