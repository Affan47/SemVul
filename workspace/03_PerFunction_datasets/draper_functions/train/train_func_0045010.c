c_parse_init (void)
{


  unsigned int i;
  tree id;
  int mask = 0;


  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  if (!flag_isoc99)
    mask |= D_C99;
  if (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      if (!flag_isoc99)
	mask |= D_EXT89;
    }
  if (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_alloc_cleared_vec_tree ((int) RID_MAX);
  for (i = 0; i < num_c_common_reswords; i++)
    {


      if (c_common_reswords[i].disable & mask)
	{
	  if (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  continue;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(int) c_common_reswords[i].rid] = id;
    }
}
