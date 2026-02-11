rest_of_decl_compilation (decl, asmspec, top_level, at_end)
     tree decl;
     const char *asmspec;
     int top_level;
     int at_end;
{


#ifndef ASM_FINISH_DECLARE_OBJECT
#define ASM_FINISH_DECLARE_OBJECT(FILE, DECL, TOP, END)
#endif


  {
    tree alias;
    alias = lookup_attribute ("alias", DECL_ATTRIBUTES (decl));
    if (alias)
      {
	alias = TREE_VALUE (TREE_VALUE (alias));
	alias = get_identifier (TREE_STRING_POINTER (alias));
	assemble_alias (decl, alias);
      }
  }


  if (TREE_STATIC (decl) || DECL_EXTERNAL (decl)
      || TREE_CODE (decl) == FUNCTION_DECL)
    {
      timevar_push (TV_VARCONST);

      if (asmspec)
	make_decl_rtl (decl, asmspec);


      if (at_end || !DECL_DEFER_OUTPUT (decl))
	assemble_variable (decl, top_level, at_end, 0);
      if (decl == last_assemble_variable_decl)
	{
	  ASM_FINISH_DECLARE_OBJECT (asm_out_file, decl,
				     top_level, at_end);
	}

      timevar_pop (TV_VARCONST);
    }
  else if (DECL_REGISTER (decl) && asmspec != 0)
    {
      if (decode_reg_name (asmspec) >= 0)
	{
	  SET_DECL_RTL (decl, NULL_RTX);
	  make_decl_rtl (decl, asmspec);
	}
      else
	{
	  error ("invalid register name `%s' for register variable", asmspec);
	  DECL_REGISTER (decl) = 0;
	  if (!top_level)
	    expand_decl (decl);
	}
    }
#if defined (DBX_DEBUGGING_INFO) || defined (XCOFF_DEBUGGING_INFO)
  else if ((write_symbols == DBX_DEBUG || write_symbols == XCOFF_DEBUG)
	   && TREE_CODE (decl) == TYPE_DECL)
    {
      timevar_push (TV_SYMOUT);
      dbxout_symbol (decl, 0);
      timevar_pop (TV_SYMOUT);
    }
#endif
#ifdef SDB_DEBUGGING_INFO
  else if (write_symbols == SDB_DEBUG && top_level
	   && TREE_CODE (decl) == TYPE_DECL)
    {
      timevar_push (TV_SYMOUT);
      sdbout_symbol (decl, 0);
      timevar_pop (TV_SYMOUT);
    }
#endif
#ifdef DWARF2_DEBUGGING_INFO
  else if ((write_symbols == DWARF2_DEBUG
	   || write_symbols == VMS_AND_DWARF2_DEBUG)
	   && top_level
	   && TREE_CODE (decl) == TYPE_DECL)
    {
      timevar_push (TV_SYMOUT);
      dwarf2out_decl (decl);
      timevar_pop (TV_SYMOUT);
    }
#endif
}
