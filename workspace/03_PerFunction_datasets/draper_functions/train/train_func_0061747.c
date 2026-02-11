gp_coffgen_blocksec(unsigned int number)
{
  gp_section_type *new = NULL;
  unsigned int i;

  if (number == 0)
    return NULL;


  new = (gp_section_type *)malloc(sizeof(*new) * number);


  number--;


  for(i = 0; i < number; i++)
    new[i].next = &new[i+1];


  new[number].next = NULL;

  return new;
}
