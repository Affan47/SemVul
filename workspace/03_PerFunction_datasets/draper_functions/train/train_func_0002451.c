linker_to_mod_or_lnk
   ___P((___mod_or_lnk (*linker) (___global_state_struct*)),
        (linker)
___mod_or_lnk (*linker) ();)
{
  ___mod_or_lnk mol = linker (&___gstate);
  if (mol->module.kind == ___LINKFILE_KIND)
    {
      void **p = mol->linkfile.linker_tbl;
      while (*p != 0)
        {
          *p = linker_to_mod_or_lnk
                 (*___CAST(___mod_or_lnk (**) ___P((___global_state_struct*),()),p));
          p++;
        }
    }
  return mol;
}
