command_line()
{
    command = new_command(false);
    if (lookahead == T_EOL) {
      if (strcmp(command->args[0],"cd") == 0){
        builtin_cd(command);
      } else if (strcmp(command->args[0],"pwd") == 0){
        builtin_pwd(command);
      } else if (strcmp(command->args[0],"exit") == 0){
        builtin_exit(command);
      } else {
        run_command(command);
      }
    }
}
