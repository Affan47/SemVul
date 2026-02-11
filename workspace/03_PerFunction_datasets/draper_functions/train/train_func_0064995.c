_bfd_elf_copy_obj_attributes (bfd *ibfd, bfd *obfd)
{
  obj_attribute *in_attr;
  obj_attribute *out_attr;
  obj_attribute_list *list;
  int i;
  int vendor;

  for (vendor = OBJ_ATTR_FIRST; vendor <= OBJ_ATTR_LAST; vendor++)
    {
      in_attr
	= &elf_known_obj_attributes (ibfd)[vendor][LEAST_KNOWN_OBJ_ATTRIBUTE];
      out_attr
	= &elf_known_obj_attributes (obfd)[vendor][LEAST_KNOWN_OBJ_ATTRIBUTE];
      for (i = LEAST_KNOWN_OBJ_ATTRIBUTE; i < NUM_KNOWN_OBJ_ATTRIBUTES; i++)
	{
	  out_attr->type = in_attr->type;
	  out_attr->i = in_attr->i;
	  if (in_attr->s && *in_attr->s)
	    out_attr->s = _bfd_elf_attr_strdup (obfd, in_attr->s);
	  in_attr++;
	  out_attr++;
	}

      for (list = elf_other_obj_attributes (ibfd)[vendor];
	   list;
	   list = list->next)
	{
	  in_attr = &list->attr;
	  switch (in_attr->type & (ATTR_TYPE_FLAG_INT_VAL | ATTR_TYPE_FLAG_STR_VAL))
	    {
	    case ATTR_TYPE_FLAG_INT_VAL:
	      bfd_elf_add_obj_attr_int (obfd, vendor, list->tag, in_attr->i);
	      break;
	    case ATTR_TYPE_FLAG_STR_VAL:
	      bfd_elf_add_obj_attr_string (obfd, vendor, list->tag,
					   in_attr->s);
	      break;
	    case ATTR_TYPE_FLAG_INT_VAL | ATTR_TYPE_FLAG_STR_VAL:
	      bfd_elf_add_obj_attr_int_string (obfd, vendor, list->tag,
					       in_attr->i, in_attr->s);
	      break;
	    default:
	      abort ();
	    }
	}
    }
}
