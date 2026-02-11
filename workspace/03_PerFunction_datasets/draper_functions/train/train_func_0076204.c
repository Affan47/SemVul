undo_all (void)
{
  struct undo *undo, *next;

  for (undo = undobuf.undos; undo; undo = next)
    {
      next = undo->next;
      switch (undo->kind)
	{
	case UNDO_RTX:
	  *undo->where.r = undo->old_contents.r;
	  break;
	case UNDO_INT:
	  *undo->where.i = undo->old_contents.i;
	  break;
	case UNDO_MODE:
	  adjust_reg_mode (*undo->where.r, undo->old_contents.m);
	  break;

	case UNDO_LINKS:
	  *undo->where.r = undo->old_contents.r;
	  break;

	default:
	  gcc_unreachable ();
	}

      undo->next = undobuf.frees;
      undobuf.frees = undo;
    }

  undobuf.undos = 0;
}
