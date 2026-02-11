output_automaton_descriptions (void)
{
  automaton_t automaton;

  for (automaton = description->first_automaton;
       automaton != NULL;
       automaton = automaton->next_automaton)
    {
      fprintf (output_description_file, "\nAutomaton ");
      output_automaton_name (output_description_file, automaton);
      fprintf (output_description_file, "\n");
      output_automaton_units (automaton);
      pass_states (automaton, output_state);
    }
}
