anim_setcommand(char *str)
{
  if (!strlen(str))
  {
    if (command == NULL)
      return;
    free(command);
    command = NULL;
  }

  if (command != NULL)
    free(command);

  command = (char *) malloc( sizeof(char) * (strlen(str) + 1) );
  sprintf(command,"%s",str);
}
