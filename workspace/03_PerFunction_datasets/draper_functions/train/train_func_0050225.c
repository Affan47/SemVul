check_cxx_fundamental_alignment_constraints (tree node,
					     unsigned align_log,
					     int flags)
{
  bool alignment_too_large_p = false;
  unsigned requested_alignment = 1U << align_log;
  unsigned max_align = 0;

  if ((!(flags & ATTR_FLAG_CXX11) && !warn_cxx_compat)
      || (node == NULL_TREE || node == error_mark_node))
    return true;

  if (cxx_fundamental_alignment_p (requested_alignment))
    return true;

  if (DECL_P (node))
    {
      if (TREE_STATIC (node))
	{


	  if (requested_alignment > (max_align = MAX_OFILE_ALIGNMENT))
	    alignment_too_large_p = true;
	}
      else
	{
#ifdef BIGGEST_FIELD_ALIGNMENT
#define MAX_TARGET_FIELD_ALIGNMENT BIGGEST_FIELD_ALIGNMENT
#else
#define MAX_TARGET_FIELD_ALIGNMENT BIGGEST_ALIGNMENT
#endif


	  max_align = MAX_TARGET_FIELD_ALIGNMENT;
	  if (TREE_CODE (node) == FIELD_DECL
	      && requested_alignment > (max_align = MAX_TARGET_FIELD_ALIGNMENT))
	    alignment_too_large_p = true;
#undef MAX_TARGET_FIELD_ALIGNMENT


	  else if (decl_function_context (node) != NULL
		   && requested_alignment > (max_align = MAX_STACK_ALIGNMENT))
	    alignment_too_large_p = true;
	}
    }
  else if (TYPE_P (node))
    {

      if (requested_alignment > (max_align = BIGGEST_ALIGNMENT))
	alignment_too_large_p = true;
    }

  if (alignment_too_large_p)
    pedwarn (input_location, OPT_Wattributes,
	     "requested alignment %d is larger than %d",
	     requested_alignment, max_align);

  return !alignment_too_large_p;
}
