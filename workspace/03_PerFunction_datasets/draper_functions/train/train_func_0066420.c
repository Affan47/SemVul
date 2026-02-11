output_reserv_sets (FILE *f, reserv_sets_t reservs)
{
  int start_cycle = 0;
  int cycle;
  int repetition_num;

  repetition_num = 0;
  for (cycle = 0; cycle < max_cycles_num; cycle++)
    if (repetition_num == 0)
      {
        repetition_num++;
        start_cycle = cycle;
      }
    else if (memcmp
             ((char *) reservs + start_cycle * els_in_cycle_reserv
	      * sizeof (set_el_t),
              (char *) reservs + cycle * els_in_cycle_reserv
	      * sizeof (set_el_t),
	      els_in_cycle_reserv * sizeof (set_el_t)) == 0)
      repetition_num++;
    else
      {
        if (start_cycle != 0)
          fprintf (f, ", ");
        output_cycle_reservs (f, reservs, start_cycle, repetition_num);
        repetition_num = 1;
        start_cycle = cycle;
      }
  if (start_cycle < max_cycles_num)
    {
      if (start_cycle != 0)
        fprintf (f, ", ");
      output_cycle_reservs (f, reservs, start_cycle, repetition_num);
    }
}
