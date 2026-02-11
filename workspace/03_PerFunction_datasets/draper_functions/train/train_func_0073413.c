tekhex_write_object_contents (bfd *abfd)
{
  char buffer[100];
  asymbol **p;
  asection *s;
  struct data_struct *d;

  tekhex_init ();


  for (d = abfd->tdata.tekhex_data->data;
       d != NULL;
       d = d->next)
    {
      int low;

      const int span = 32;
      int addr;


      for (addr = 0; addr < CHUNK_MASK + 1; addr += span)
	{
	  int need = 0;


	  for (low = 0; !need && low < span; low++)
	    if (d->chunk_init[addr + low])
	      need = 1;

	  if (need)
	    {
	      char *dst = buffer;

	      writevalue (&dst, addr + d->vma);
	      for (low = 0; low < span; low++)
		{
		  TOHEX (dst, d->chunk_data[addr + low]);
		  dst += 2;
		}
	      out (abfd, '6', buffer, dst);
	    }
	}
    }


  for (s = abfd->sections; s != NULL; s = s->next)
    {
      char *dst = buffer;

      writesym (&dst, s->name);
      *dst++ = '1';
      writevalue (&dst, s->vma);
      writevalue (&dst, s->vma + s->size);
      out (abfd, '3', buffer, dst);
    }


  if (abfd->outsymbols)
    {
      for (p = abfd->outsymbols; *p; p++)
	{
	  int section_code = bfd_decode_symclass (*p);

	  if (section_code != '?')
	    {

	      asymbol *sym = *p;
	      char *dst = buffer;

	      writesym (&dst, sym->section->name);

	      switch (section_code)
		{
		case 'A':
		  *dst++ = '2';
		  break;
		case 'a':
		  *dst++ = '6';
		  break;
		case 'D':
		case 'B':
		case 'O':
		  *dst++ = '4';
		  break;
		case 'd':
		case 'b':
		case 'o':
		  *dst++ = '8';
		  break;
		case 'T':
		  *dst++ = '3';
		  break;
		case 't':
		  *dst++ = '7';
		  break;
		case 'C':
		case 'U':
		  bfd_set_error (bfd_error_wrong_format);
		  return FALSE;
		}

	      writesym (&dst, sym->name);
	      writevalue (&dst, sym->value + sym->section->vma);
	      out (abfd, '3', buffer, dst);
	    }
	}
    }


  if (bfd_bwrite ("%0781010\n", (bfd_size_type) 9, abfd) != 9)
    abort ();
  return TRUE;
}
