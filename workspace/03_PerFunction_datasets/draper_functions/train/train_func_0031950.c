pars_amino_acid(char *formel)
{
  while(*formel)
    {
      if(!add_amino_acid(*formel))
	return 0;
      *formel++;
    }
  add_component("O",1);
  add_component("H",2);

  return 1;
}
