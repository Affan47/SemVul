undef_to_size_word (reg, undefined)
     rtx reg;
     unsigned HOST_WIDE_INT *undefined;
{


  if (*undefined <= 15)
    {
      struct undef_table_s u;
      u = undef_table[*undefined];
      *undefined = u.new_undef;
      return u.size_word;
    }


  switch (*undefined)
    {
      case 0x00f0 : *undefined = 0; return BL_TO_WORD (4, 4);
      case 0x00ff : *undefined = 0; return BL_TO_WORD (0, 8);
      case 0x0f00 : *undefined = 0; return BL_TO_WORD (8, 4);
      case 0x0ff0 : *undefined = 0xf0; return BL_TO_WORD (8, 4);
      case 0x0fff :
	if (INTEGRAL_MODE_P (GET_MODE (reg)))
	  { *undefined = 0xff; return BL_TO_WORD (8, 4); }
	else
	  { *undefined = 0; return BL_TO_WORD (0, 12);  }
      case 0xf000 : *undefined = 0; return BL_TO_WORD (12, 4);
      case 0xff00 : *undefined = 0; return BL_TO_WORD (8, 8);
      case 0xfff0 : *undefined = 0xf0; return BL_TO_WORD (8, 8);
      case 0xffff : *undefined = 0; return BL_TO_WORD (0, 16);


      default :
	{
	  unsigned HOST_WIDE_INT u = *undefined;
	  int word;
	  struct undef_table_s tab;
	  for (word = 0; (u & 15) == 0; word += 4)
	    u >>= 4;
	  u = u & 15;
	  tab = undef_table[u];
	  u = tab.new_undef;
	  u = (*undefined & ~((unsigned HOST_WIDE_INT)15 << word))
	      | (u << word);
	  *undefined = u;

	  return tab.size_word + BL_TO_WORD (word, 0);
	}
	break;
    }
}
