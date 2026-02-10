check_function_arguments (const_tree fntype, int nargs, tree *argarray)
{


  if (warn_nonnull)
    check_function_nonnull (TYPE_ATTRIBUTES (fntype), nargs, argarray);


  if (warn_format || warn_suggest_attribute_format)
    check_function_format (TYPE_ATTRIBUTES (fntype), nargs, argarray);

  if (warn_format)
    check_function_sentinel (fntype, nargs, argarray);
}
