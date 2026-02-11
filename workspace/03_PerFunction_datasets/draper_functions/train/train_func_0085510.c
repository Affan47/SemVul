dump_choices (bool speed_p, const char *description)
{
  unsigned int i;

  fprintf (dump_file, "Choices when optimizing for %s:\n", description);

  for (i = 0; i < MAX_MACHINE_MODE; i++)
    if (GET_MODE_SIZE (i) > UNITS_PER_WORD)
      fprintf (dump_file, "  %s mode %s for copy lowering.\n",
	       choices[speed_p].move_modes_to_split[i]
	       ? "Splitting"
	       : "Skipping",
	       GET_MODE_NAME ((enum machine_mode) i));

  fprintf (dump_file, "  %s mode %s for zero_extend lowering.\n",
	   choices[speed_p].splitting_zext ? "Splitting" : "Skipping",
	   GET_MODE_NAME (twice_word_mode));

  dump_shift_choices (ASHIFT, choices[speed_p].splitting_ashift);
  dump_shift_choices (LSHIFTRT, choices[speed_p].splitting_lshiftrt);
  dump_shift_choices (ASHIFTRT, choices[speed_p].splitting_ashiftrt);
  fprintf (dump_file, "\n");
}
