___os_create_symbolic_link
   ___P((___SCMOBJ path1,
         ___SCMOBJ path2),
        (path1,
         path2)
___SCMOBJ path1;
___SCMOBJ path2;)
{
  ___SCMOBJ e;
  void *cpath1;
  void *cpath2;

#ifndef USE_symlink

  e = ___FIX(___UNIMPL_ERR);

#endif

#ifdef USE_symlink

#define ___CREATE_SYMLINK_PATH_CE_SELECT(latin1,utf8,ucs2,ucs4,wchar,native) native

  if ((e = ___SCMOBJ_to_NONNULLSTRING
             (path1,
              &cpath1,
              1,
              ___CE(___CREATE_SYMLINK_PATH_CE_SELECT),
              0))
      == ___FIX(___NO_ERR))
    {
      if ((e = ___SCMOBJ_to_NONNULLSTRING
                 (path2,
                  &cpath2,
                  2,
                  ___CE(___CREATE_SYMLINK_PATH_CE_SELECT),
                  0))
          == ___FIX(___NO_ERR))
        {
          if (symlink (___CAST(___STRING_TYPE(___CREATE_SYMLINK_PATH_CE_SELECT),cpath1),
                       ___CAST(___STRING_TYPE(___CREATE_SYMLINK_PATH_CE_SELECT),cpath2))
              < 0)
            e = fnf_or_err_code_from_errno ();
          ___release_string (cpath2);
        }
      ___release_string (cpath1);
    }

#endif

  return e;
}
