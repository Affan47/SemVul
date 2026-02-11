globalize_decl (decl)
     tree decl;
{
  const char *name = XSTR (XEXP (DECL_RTL (decl), 0), 0);

#if defined (ASM_WEAKEN_LABEL) || defined (ASM_WEAKEN_DECL)
  if (DECL_WEAK (decl))
    {
      tree *p, t;

#ifdef ASM_WEAKEN_DECL
      ASM_WEAKEN_DECL (asm_out_file, decl, name, 0);
#else
      ASM_WEAKEN_LABEL (asm_out_file, name);
#endif


      for (p = &weak_decls; (t = *p) ; )
	{
	  if (DECL_ASSEMBLER_NAME (decl) == DECL_ASSEMBLER_NAME (TREE_VALUE (t)))
	    *p = TREE_CHAIN (t);
	  else
	    p = &TREE_CHAIN (t);
	}
      return;
    }
#endif

  (*targetm.asm_out.globalize_label) (asm_out_file, name);
}
