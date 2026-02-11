stack_depth (scm_t_debug_frame *dframe, scm_t_ptrdiff offset,
	     SCM *id, int *maxp)
{
  long n;
  long max_depth = SCM_BACKTRACE_MAXDEPTH;
  for (n = 0;
       dframe && !SCM_VOIDFRAMEP (*dframe) && n < max_depth;
       dframe = RELOC_FRAME (dframe->prev, offset))
    {
      if (SCM_EVALFRAMEP (*dframe))
	{
	  scm_t_debug_info *info = RELOC_INFO (dframe->info, offset);
	  scm_t_debug_info *vect = RELOC_INFO (dframe->vect, offset);
	  n += (info - vect) / 2 + 1;


	  if ((((info - vect) & 1) == 0)
	      && SCM_OVERFLOWP (*dframe)
	      && !SCM_UNBNDP (info[1].a.proc))
	    ++n;
	}
      else
	++n;
    }
  if (dframe && SCM_VOIDFRAMEP (*dframe))
    *id = RELOC_INFO(dframe->vect, offset)[0].id;
  else if (dframe)
    *maxp = 1;
  return n;
}
