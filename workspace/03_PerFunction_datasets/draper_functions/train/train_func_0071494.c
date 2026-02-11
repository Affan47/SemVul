fold_unary (etree_type *tree)
{
  exp_fold_tree_1 (tree->unary.child);
  if (expld.result.valid_p)
    {
      switch (tree->type.node_code)
	{
	case ALIGN_K:
	  if (expld.phase != lang_first_phase_enum)
	    new_rel_from_abs (align_n (expld.dot, expld.result.value));
	  else
	    expld.result.valid_p = FALSE;
	  break;

	case ABSOLUTE:
	  make_abs ();
	  break;

	case '~':
	  expld.result.value = ~expld.result.value;
	  break;

	case '!':
	  expld.result.value = !expld.result.value;
	  break;

	case '-':
	  expld.result.value = -expld.result.value;
	  break;

	case NEXT:

	  if (expld.phase != lang_first_phase_enum)
	    {
	      make_abs ();
	      expld.result.value = align_n (expld.dot, expld.result.value);
	    }
	  else
	    expld.result.valid_p = FALSE;
	  break;

	case DATA_SEGMENT_END:
	  if (expld.phase == lang_first_phase_enum
	      || expld.section != bfd_abs_section_ptr)
	    {
	      expld.result.valid_p = FALSE;
	    }
	  else if (expld.dataseg.phase == exp_dataseg_align_seen
		   || expld.dataseg.phase == exp_dataseg_relro_seen)
	    {
	      expld.dataseg.phase = exp_dataseg_end_seen;
	      expld.dataseg.end = expld.result.value;
	    }
	  else if (expld.dataseg.phase == exp_dataseg_done
		   || expld.dataseg.phase == exp_dataseg_adjust
		   || expld.dataseg.phase == exp_dataseg_relro_adjust)
	    {

	    }
	  else
	    expld.result.valid_p = FALSE;
	  break;

	default:
	  FAIL ();
	  break;
	}
    }
}
