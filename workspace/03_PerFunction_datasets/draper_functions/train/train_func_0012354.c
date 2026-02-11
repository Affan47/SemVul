xtensa_isa_free (xtensa_isa isa)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int n;


  if (intisa->opname_lookup_table)
    {
      free (intisa->opname_lookup_table);
      intisa->opname_lookup_table = 0;
    }

  if (intisa->state_lookup_table)
    {
      free (intisa->state_lookup_table);
      intisa->state_lookup_table = 0;
    }

  if (intisa->sysreg_lookup_table)
    {
      free (intisa->sysreg_lookup_table);
      intisa->sysreg_lookup_table = 0;
    }
  for (n = 0; n < 2; n++)
    {
      if (intisa->sysreg_table[n])
	{
	  free (intisa->sysreg_table[n]);
	  intisa->sysreg_table[n] = 0;
	}
    }

  if (intisa->interface_lookup_table)
    {
      free (intisa->interface_lookup_table);
      intisa->interface_lookup_table = 0;
    }

  if (intisa->funcUnit_lookup_table)
    {
      free (intisa->funcUnit_lookup_table);
      intisa->funcUnit_lookup_table = 0;
    }
}
