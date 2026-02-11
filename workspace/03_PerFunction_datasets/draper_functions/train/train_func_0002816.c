cmd_colon (int interactive UNUSED, struct cmdarg **args)
{
  cmdret *result;
  char *input;

  if (args[0] == NULL)
    input = get_input (MESSAGE_PROMPT_COMMAND, hist_COMMAND, colon_completions);
  else
    input = get_more_input (MESSAGE_PROMPT_COMMAND, ARG_STRING(0), hist_COMMAND,
			    colon_completions);


  if (input == NULL)
    return cmdret_new (RET_FAILURE, NULL);

  result = command (1, input);
  free (input);
  return result;
}
