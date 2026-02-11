simple_object_mach_o_write_header (simple_object_write *sobj, int descriptor,
				   size_t nsects, const char **errmsg,
				   int *err)
{
  struct simple_object_mach_o_attributes *attrs =
    (struct simple_object_mach_o_attributes *) sobj->data;
  void (*set_32) (unsigned char *, unsigned int);
  unsigned char hdrbuf[sizeof (struct mach_o_header_64)];
  unsigned char *hdr;
  size_t wrsize;

  set_32 = (attrs->is_big_endian
	    ? simple_object_set_big_32
	    : simple_object_set_little_32);

  memset (hdrbuf, 0, sizeof hdrbuf);


  hdr = &hdrbuf[0];
  set_32 (hdr + offsetof (struct mach_o_header_32, magic), attrs->magic);
  set_32 (hdr + offsetof (struct mach_o_header_32, cputype), attrs->cputype);
  set_32 (hdr + offsetof (struct mach_o_header_32, cpusubtype),
	  attrs->cpusubtype);
  set_32 (hdr + offsetof (struct mach_o_header_32, filetype), MACH_O_MH_OBJECT);
  set_32 (hdr + offsetof (struct mach_o_header_32, ncmds), 1);
  set_32 (hdr + offsetof (struct mach_o_header_32, flags), attrs->flags);
  if (attrs->magic == MACH_O_MH_MAGIC)
    {
      wrsize = sizeof (struct mach_o_header_32);
      set_32 (hdr + offsetof (struct mach_o_header_32, sizeofcmds),
	      (sizeof (struct mach_o_segment_command_32)
	       + nsects * sizeof (struct mach_o_section_32)));
    }
  else
    {
      set_32 (hdr + offsetof (struct mach_o_header_64, sizeofcmds),
	      (sizeof (struct mach_o_segment_command_64)
	       + nsects * sizeof (struct mach_o_section_64)));
      set_32 (hdr + offsetof (struct mach_o_header_64, reserved),
	      attrs->reserved);
      wrsize = sizeof (struct mach_o_header_64);
    }

  return simple_object_internal_write (descriptor, 0, hdrbuf, wrsize,
				       errmsg, err);
}
