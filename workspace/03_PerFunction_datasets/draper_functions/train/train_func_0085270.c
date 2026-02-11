modperl_module_cmd_lookup(command_rec *cmd)
{
    switch (cmd->args_how) {
      case TAKE1:
      case ITERATE:
        modperl_module_cmd_func_set(cmd, take1);
        break;
      case TAKE2:
      case ITERATE2:
      case TAKE12:
        modperl_module_cmd_func_set(cmd, take2);
        break;
      case TAKE3:
      case TAKE23:
      case TAKE123:
      case TAKE13:
        modperl_module_cmd_func_set(cmd, take3);
        break;
      case RAW_ARGS:
        modperl_module_cmd_func_set(cmd, raw_args);
        break;
      case FLAG:
        modperl_module_cmd_func_set(cmd, flag);
        break;
      case NO_ARGS:
        modperl_module_cmd_func_set(cmd, no_args);
        break;
      default:
        return FALSE;
    }

    return TRUE;
}
