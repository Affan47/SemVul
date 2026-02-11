filter_symbols (syms, symcount)
     struct nlist *syms;
     unsigned int symcount;
{
  struct nlist *from, *to;
  struct nlist *end = syms + symcount;

  for (to = from = syms; from < end; ++from)
    if ((from->n_type & N_EXT)
	&& (from->n_type != N_EXT || from->n_value != 0))
      *to++ = *from;

  return to - syms;
}
