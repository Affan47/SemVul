unqualified_fn_lookup_error (tree name)
{
  if (processing_template_decl)
    {


      pedwarn ("there are no arguments to `%D' that depend on a template "
	       "parameter, so a declaration of `%D' must be available",
	       name, name);

      if (!flag_permissive)
	{
	  static bool hint;
	  if (!hint)
	    {
	      error ("(if you use `-fpermissive', G++ will accept your code, "
		     "but allowing the use of an undeclared name is "
		     "deprecated)");
	      hint = true;
	    }
	}
      return name;
    }

  return unqualified_name_lookup_error (name);
}
