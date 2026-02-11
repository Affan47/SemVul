output_internal_dead_lock_func ()
{
  automaton_t automaton;

  fprintf (output_file, "static int %s PARAMS ((struct %s *));\n",
	   INTERNAL_DEAD_LOCK_FUNC_NAME, CHIP_NAME);
  fprintf (output_file, "static int\n%s (%s)\n\tstruct %s *%s;\n",
	   INTERNAL_DEAD_LOCK_FUNC_NAME, CHIP_PARAMETER_NAME, CHIP_NAME,
	   CHIP_PARAMETER_NAME);
  fprintf (output_file, "{\n");
  for (automaton = description->first_automaton;
       automaton != NULL;
       automaton = automaton->next_automaton)
    {
      fprintf (output_file, "  if (");
      output_dead_lock_vect_name (output_file, automaton);
      fprintf (output_file, " [%s->", CHIP_PARAMETER_NAME);
      output_chip_member_name (output_file, automaton);
      fprintf (output_file, "])\n    return 1/* TRUE */;\n");
    }
  fprintf (output_file, "  return 0/* FALSE */;\n}\n\n");
}
