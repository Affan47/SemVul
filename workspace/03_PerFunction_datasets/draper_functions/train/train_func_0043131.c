split_sections (bfd *abfd, struct bfd_link_info *info)
{
  asection *original_sec;
  int nsecs = abfd->section_count;
  sanity_check (abfd);

  for (original_sec = abfd->sections;
       original_sec && nsecs;
       original_sec = original_sec->next, nsecs--)
    {
      int count = 0;
      unsigned int lines = 0;
      unsigned int relocs = 0;
      bfd_size_type sec_size = 0;
      struct bfd_link_order *l;
      struct bfd_link_order *p;
      bfd_vma vma = original_sec->vma;
      asection *cursor = original_sec;


      for (l = NULL, p = cursor->map_head.link_order; p != NULL; p = l->next)
	{
	  unsigned int thislines = 0;
	  unsigned int thisrelocs = 0;
	  bfd_size_type thissize = 0;
	  if (p->type == bfd_indirect_link_order)
	    {
	      asection *sec;

	      sec = p->u.indirect.section;

	      if (info->strip == strip_none
		  || info->strip == strip_some)
		thislines = sec->lineno_count;

	      if (info->relocatable)
		thisrelocs = sec->reloc_count;

	      thissize = sec->size;

	    }
	  else if (info->relocatable
		   && (p->type == bfd_section_reloc_link_order
		       || p->type == bfd_symbol_reloc_link_order))
	    thisrelocs++;

	  if (l != NULL
	      && (thisrelocs + relocs >= config.split_by_reloc
		  || thislines + lines >= config.split_by_reloc
		  || (thissize + sec_size >= config.split_by_file))
	      && !unsplittable_name (cursor->name))
	    {


	      bfd_vma shift_offset;
	      asection *n;

	      n = clone_section (abfd, cursor, original_sec->name, &count);


	      n->map_head.link_order = p;
	      n->map_tail.link_order = cursor->map_tail.link_order;
	      cursor->map_tail.link_order = l;
	      l->next = NULL;
	      l = p;


	      dump ("before snip", cursor, n);

	      shift_offset = p->offset;
	      n->size = cursor->size - shift_offset;
	      cursor->size = shift_offset;

	      vma += shift_offset;
	      n->lma = n->vma = vma;


	      do
		{
		  p->offset -= shift_offset;
		  if (p->type == bfd_indirect_link_order)
		    {
		      p->u.indirect.section->output_section = n;
		      p->u.indirect.section->output_offset = p->offset;
		    }
		  p = p->next;
		}
	      while (p);

	      dump ("after snip", cursor, n);
	      cursor = n;
	      relocs = thisrelocs;
	      lines = thislines;
	      sec_size = thissize;
	    }
	  else
	    {
	      l = p;
	      relocs += thisrelocs;
	      lines += thislines;
	      sec_size += thissize;
	    }
	}
    }
  sanity_check (abfd);
}
