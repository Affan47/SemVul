cofix ()
{

  union fix      *fixp_arch;

  fixp_arch = fixp;

  while (IF == fixp->if1.major)
    fixp--;

  if (fixp == (union fix *) fixst)
    {
      error_message (3001);
      return (-1);
    }
  if (WHILE == fixp->while1.major)
    {
      struct cont1   *cp;

      if (NULL == fixp->while1.cnext)
	{
#ifdef DEBUG
	  printfx ("continue in while fixed\n");
#endif
	  fixp->while1.cnext = (struct cont1 *)
	    allocate (sizeof (struct cont1), BLOCK);
	  fixp->while1.cnext->adr = kodp;
	  fixp->while1.cnext->next = NULL;
	}
      else
	{
	  cp = fixp->while1.cnext;
	  while (NULL != cp->next)
	    cp = cp->next;

#ifdef DEBUG
	  printfx ("continue in while fixed\n");
#endif
	  cp->next = (struct cont1 *)
	    allocate (sizeof (struct cont1), BLOCK);
	  cp->next->adr = kodp;
	  cp->next->next = NULL;
	}
    }
  if (FOR == fixp->for1.major)
    {
      struct cont1   *cp;

      if (NULL == fixp->for1.cnext)
	{
#ifdef DEBUG
	  printfx ("continue in for fixed\n");
#endif
	  fixp->for1.cnext = (struct cont1 *)
	    allocate (sizeof (struct cont1), BLOCK);
	  fixp->for1.cnext->adr = kodp;
	  fixp->for1.cnext->next = NULL;
	}
      else
	{
	  cp = fixp->for1.cnext;
	  while (NULL != cp->next)
	    cp = cp->next;
#ifdef DEBUG
	  printfx ("continue in for fixed\n");
#endif
	  cp->next = (struct cont1 *)
	    allocate (sizeof (struct cont1), BLOCK);
	  cp->next->adr = kodp;
	  cp->next->next = NULL;
	}
    }
  fixp = fixp_arch;
  return (0);
}
