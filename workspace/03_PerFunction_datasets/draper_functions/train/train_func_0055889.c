final_start_function (rtx first ATTRIBUTE_UNUSED, FILE *file,
		      int optimize ATTRIBUTE_UNUSED)
{
  block_depth = 0;

  this_is_asm_operands = 0;

  last_filename = locator_file (prologue_locator);
  last_linenum = locator_line (prologue_locator);

  high_block_linenum = high_function_linenum = last_linenum;

  (*debug_hooks->begin_prologue) (last_linenum, last_filename);

#if defined (DWARF2_UNWIND_INFO) || defined (IA64_UNWIND_INFO)
  if (write_symbols != DWARF2_DEBUG && write_symbols != VMS_AND_DWARF2_DEBUG)
    dwarf2out_begin_prologue (0, NULL);
#endif

#ifdef LEAF_REG_REMAP
  if (current_function_uses_only_leaf_regs)
    leaf_renumber_regs (first);
#endif


#ifdef PROFILE_BEFORE_PROLOGUE
  if (current_function_profile)
    profile_function (file);
#endif

#if defined (DWARF2_UNWIND_INFO) && defined (HAVE_prologue)
  if (dwarf2out_do_frame ())
    dwarf2out_frame_debug (NULL_RTX);
#endif


  if (write_symbols)
    {
      remove_unnecessary_notes ();
      reemit_insn_block_notes ();
      number_blocks (current_function_decl);


      TREE_ASM_WRITTEN (DECL_INITIAL (current_function_decl)) = 1;
    }


  (*targetm.asm_out.function_prologue) (file, get_frame_size ());


#ifdef HAVE_prologue
  if (! HAVE_prologue)
#endif
    profile_after_prologue (file);
}
