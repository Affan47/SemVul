generic_link_add_symbol_list (bfd *abfd,
			      struct bfd_link_info *info,
			      bfd_size_type symbol_count,
			      asymbol **symbols,
			      bfd_boolean collect)
{
  asymbol **pp, **ppend;

  pp = symbols;
  ppend = symbols + symbol_count;
  for (; pp < ppend; pp++)
    {
      asymbol *p;

      p = *pp;

      if ((p->flags & (BSF_INDIRECT
		       | BSF_WARNING
		       | BSF_GLOBAL
		       | BSF_CONSTRUCTOR
		       | BSF_WEAK)) != 0
	  || bfd_is_und_section (bfd_get_section (p))
	  || bfd_is_com_section (bfd_get_section (p))
	  || bfd_is_ind_section (bfd_get_section (p)))
	{
	  const char *name;
	  const char *string;
	  struct generic_link_hash_entry *h;
	  struct bfd_link_hash_entry *bh;

	  string = name = bfd_asymbol_name (p);
	  if (((p->flags & BSF_INDIRECT) != 0
	       || bfd_is_ind_section (p->section))
	      && pp + 1 < ppend)
	    {
	      pp++;
	      string = bfd_asymbol_name (*pp);
	    }
	  else if ((p->flags & BSF_WARNING) != 0
		   && pp + 1 < ppend)
	    {


	      pp++;
	      name = bfd_asymbol_name (*pp);
	    }

	  bh = NULL;
	  if (! (_bfd_generic_link_add_one_symbol
		 (info, abfd, name, p->flags, bfd_get_section (p),
		  p->value, string, FALSE, collect, &bh)))
	    return FALSE;
	  h = (struct generic_link_hash_entry *) bh;


	  if ((p->flags & BSF_CONSTRUCTOR) != 0
	      && (h == NULL || h->root.type == bfd_link_hash_new))
	    {
	      p->udata.p = NULL;
	      continue;
	    }


	  if (info->output_bfd->xvec == abfd->xvec)
	    {
	      if (h->sym == NULL
		  || (! bfd_is_und_section (bfd_get_section (p))
		      && (! bfd_is_com_section (bfd_get_section (p))
			  || bfd_is_und_section (bfd_get_section (h->sym)))))
		{
		  h->sym = p;


		  if (bfd_is_com_section (bfd_get_section (p)))
		    p->flags |= BSF_OLD_COMMON;
		}
	    }


	  p->udata.p = h;
	}
    }

  return TRUE;
}
