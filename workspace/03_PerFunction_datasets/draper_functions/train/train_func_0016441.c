copy_command (command)
     COMMAND *command;
{
  COMMAND *new_command;

  if (command == NULL)
    return (command);

  new_command = (COMMAND *)xmalloc (sizeof (COMMAND));
  FASTCOPY ((char *)command, (char *)new_command, sizeof (COMMAND));
  new_command->flags = command->flags;
  new_command->line = command->line;

  if (command->redirects)
    new_command->redirects = copy_redirects (command->redirects);

  switch (command->type)
    {
      case cm_for:
	new_command->value.For = copy_for_command (command->value.For);
	break;

#if defined (ARITH_FOR_COMMAND)
      case cm_arith_for:
	new_command->value.ArithFor = copy_arith_for_command (command->value.ArithFor);
	break;
#endif

#if defined (SELECT_COMMAND)
      case cm_select:
	new_command->value.Select =
	  (SELECT_COM *)copy_for_command ((FOR_COM *)command->value.Select);
	break;
#endif

      case cm_group:
	new_command->value.Group = copy_group_command (command->value.Group);
	break;

      case cm_subshell:
	new_command->value.Subshell = copy_subshell_command (command->value.Subshell);
	break;

      case cm_coproc:
	new_command->value.Coproc = copy_coproc_command (command->value.Coproc);
	break;

      case cm_case:
	new_command->value.Case = copy_case_command (command->value.Case);
	break;

      case cm_until:
      case cm_while:
	new_command->value.While = copy_while_command (command->value.While);
	break;

      case cm_if:
	new_command->value.If = copy_if_command (command->value.If);
	break;

#if defined (DPAREN_ARITHMETIC)
      case cm_arith:
	new_command->value.Arith = copy_arith_command (command->value.Arith);
	break;
#endif

#if defined (COND_COMMAND)
      case cm_cond:
	new_command->value.Cond = copy_cond_command (command->value.Cond);
	break;
#endif

      case cm_simple:
	new_command->value.Simple = copy_simple_command (command->value.Simple);
	break;

      case cm_connection:
	{
	  CONNECTION *new_connection;

	  new_connection = (CONNECTION *)xmalloc (sizeof (CONNECTION));
	  new_connection->connector = command->value.Connection->connector;
	  new_connection->first = copy_command (command->value.Connection->first);
	  new_connection->second = copy_command (command->value.Connection->second);
	  new_command->value.Connection = new_connection;
	  break;
	}

      case cm_function_def:
	new_command->value.Function_def = copy_function_def (command->value.Function_def);
	break;
    }
  return (new_command);
}
