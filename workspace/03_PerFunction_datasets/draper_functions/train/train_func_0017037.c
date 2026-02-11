Main_Wrapper(int argc, char *argv[])
{
  int i;
  int new_argc = 0;
  char **new_argv;
  WamWord *entry_goal;
  int nb_entry_goal = 0;
  WamWord *query_goal;
  int nb_query_goal = 0;
  WamWord word;


  Start_Prolog(argc, argv);

  new_argv = (char **) Malloc(sizeof(char *) * (argc + 1));
  new_argv[new_argc++] = argv[0];

  entry_goal = (WamWord *) Malloc(sizeof(WamWord) * argc);
  query_goal = (WamWord *) Malloc(sizeof(WamWord) * argc);

  for (i = 1; i < argc; i++)
    {
      if (*argv[i] == '-' && argv[i][1] != '\0')
	{
	  if (strcmp(argv[i], "--") == 0)
	    {
	      i++;
	      break;
	    }

	  if (Check_Arg(i, "--version"))
	    {
	      Display_Copying("Prolog top-Level");
	      exit(0);
	    }

	  if (Check_Arg(i, "--init-goal"))
	    {
	      if (++i >= argc)
		Fatal_Error("Goal missing after --init-goal option");

	      A(0) = Tag_ATM(Create_Atom(argv[i]));
	      Call_Prolog(Prolog_Predicate(EXEC_CMD_LINE_GOAL, 1));
	      Reset_Prolog();
	      continue;
	    }

	  if (Check_Arg(i, "--entry-goal"))
	    {
	      if (++i >= argc)
		Fatal_Error("Goal missing after --entry-goal option");

	      entry_goal[nb_entry_goal++] = Tag_ATM(Create_Atom(argv[i]));
	      continue;
	    }

	  if (Check_Arg(i, "--query-goal"))
	    {
	      if (++i >= argc)
		Fatal_Error("Goal missing after --query-goal option");

	      query_goal[nb_query_goal++] = Tag_ATM(Create_Atom(argv[i]));
	      continue;
	    }

	  if (Check_Arg(i, "-h") || Check_Arg(i, "--help"))
	    {
	      Display_Help();
	      exit(0);
	    }
	}

      new_argv[new_argc++] = argv[i];
    }

  while(i < argc)
    new_argv[new_argc++] = argv[i++];

  new_argv[new_argc] = NULL;

  os_argc = new_argc;
  os_argv = new_argv;

  if (nb_entry_goal)
    {
      word = Mk_Proper_List(nb_entry_goal, entry_goal);
      Blt_G_Assign(Tag_ATM(Create_Atom("$cmd_line_entry_goal")), word);
    }
  Free(entry_goal);

  if (nb_query_goal)
    {
      word = Mk_Proper_List(nb_query_goal, query_goal);
      Blt_G_Assign(Tag_ATM(Create_Atom("$cmd_line_query_goal")), word);
    }
  Free(query_goal);

  Reset_Prolog();
  Call_Prolog(Prolog_Predicate(PREDICATE_TOP_LEVEL, 0));

  Stop_Prolog();
  return 0;
}
