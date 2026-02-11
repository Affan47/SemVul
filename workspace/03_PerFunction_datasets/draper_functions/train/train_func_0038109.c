write_function_unit_info ()
{
  struct function_unit *unit;
  int i;


  for (unit = units; unit; unit = unit->next)
    {
      if (unit->needs_blockage_function)
	write_complex_function (unit, "blockage", "block");


      if (! unit->needs_conflict_function)
	{
	  unit->default_cost = make_numeric_value (unit->issue_delay.max);
	  continue;
	}


      unit->default_cost = make_numeric_value (0);
      write_complex_function (unit, "conflict_cost", "cost");
    }


  printf ("const struct function_unit_desc function_units[] = {\n");


  for (i = 0; i < num_units; i++)
    {
      for (unit = units; unit; unit = unit->next)
	if (unit->num == i)
	  break;

      printf ("  {\"%s\", %d, %d, %d, %s, %d, %s_unit_ready_cost, ",
	      unit->name, 1 << unit->num, unit->multiplicity,
	      unit->simultaneity, XSTR (unit->default_cost, 0),
	      unit->issue_delay.max, unit->name);

      if (unit->needs_conflict_function)
	printf ("%s_unit_conflict_cost, ", unit->name);
      else
	printf ("0, ");

      printf ("%d, ", unit->max_blockage);

      if (unit->needs_range_function)
	printf ("%s_unit_blockage_range, ", unit->name);
      else
	printf ("0, ");

      if (unit->needs_blockage_function)
	printf ("%s_unit_blockage", unit->name);
      else
	printf ("0");

      printf ("}, \n");
    }

  if (num_units == 0)
    printf ("{\"dummy\", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} /* a dummy element */");
  printf ("};\n\n");
}
