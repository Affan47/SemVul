p_atom(int i)
{
  int j;
  Atom_ptr a = Atoms + i;

  printf("Atom=%d, value=%d, pos_occ=", i, a->value);
  for (j = 0; j < a->num_pos_occ; j++)
    printf("%x,", (unsigned) a->pos_occ[j]);
  printf(" neg_occ=");
  for (j = 0; j < a->num_neg_occ; j++)
    printf("%x,", (unsigned) a->neg_occ[j]);
  printf(".\n");
}
