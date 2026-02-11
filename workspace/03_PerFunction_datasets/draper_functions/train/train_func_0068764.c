restore_context ()
{
  struct CONTEXT *arch;
  if (context != NULL)
    {
      if (kodp2 == kodp1)
	{
	  kodp = context->kodp;
	  kodp1 = context->kodp1;
	  kodp2 = context->kodp2;
	  kodp3 = context->kodp3;
	  kodp4 = context->kodp4;
	}
      arch = context;
      bp = context->bp;
      frame = context->frame;
      pc = context->pc;
      stack = context->stack;
      tmp = context->tmp;
      tmph = context->tmph;
#ifdef FLEX_SCANNER
      flush_buffer (context->state);
#else
      input = context->input;
#endif
      context = context->previous;
      free (arch);
    }
}
