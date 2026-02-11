model(int depth)
{
  int i;

  if (MACE_Flags[RECORD_ASSIGNMENTS].val)
    print_assignments(depth);

  Models++;
  if (MACE_Flags[PRINT_MODELS].val) {
    if (!First_order) {
      printf("\nModel #%d:", Models);
      for (i = 1; i <= Greatest_atom; i++)
	if (Atoms[i].value == ATOM_TRUE)
	  printf(" %d", i);
      printf("\n");
      printf("end_of_model\n");
    }
    else
      print_model(stdout);
  }

  if (MACE_Flags[PRINT_MODELS_PORTABLE].val) {
    if (!First_order) {
      printf("\nModel #%d:", Models);
      for (i = 1; i <= Greatest_atom; i++)
	if (Atoms[i].value == ATOM_TRUE)
	  printf(" %d", i);
      printf("\n");
      printf("end_of_model\n");
    }
    else
      print_model_portable(stdout);
  }

  if (MACE_Flags[PRINT_MODELS_IVY].val) {
    if (!First_order) {
      printf("\nModel #%d:", Models);
      for (i = 1; i <= Greatest_atom; i++)
	if (Atoms[i].value == ATOM_TRUE)
	  printf(" %d", i);
      printf("\n");
      printf("end_of_model\n");
    }
    else
      print_model_ivy(stdout);
  }

  if (!MACE_Flags[PRINT_MODELS_PORTABLE].val && !MACE_Flags[PRINT_MODELS].val) {
    if (Models == Next_message) {
      printf("\nThe %d%s model has been found.\n", Models,
	     Next_message == 1 ? "st" : "th");
      Next_message *= 10;
    }
  }

  fflush(stdout);

  if (Models >= MACE_Parms[MAX_MODELS].val)
    exit_with_message(MAX_MODELS_EXIT, 1);
}
