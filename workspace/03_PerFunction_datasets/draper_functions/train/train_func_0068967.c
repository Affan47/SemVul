fold_upward_gf_methods (SCM method_lists, SCM gf)
{
  if (SCM_IS_A_P (gf, scm_class_extended_generic))
    {
      SCM gfs = scm_slot_ref (gf, sym_extends);
      while (!scm_is_null (gfs))
	{
	  SCM methods = scm_slot_ref (SCM_CAR (gfs), sym_methods);
	  method_lists = fold_upward_gf_methods (scm_cons (methods,
							   method_lists),
						 SCM_CAR (gfs));
	  gfs = SCM_CDR (gfs);
	}
    }
  return method_lists;
}
