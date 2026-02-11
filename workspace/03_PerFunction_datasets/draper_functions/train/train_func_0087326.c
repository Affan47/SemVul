equal_functions (tree fn1, tree fn2)
{
  if (DECL_LOCAL_FUNCTION_P (fn1) || DECL_LOCAL_FUNCTION_P (fn2)
      || DECL_EXTERN_C_FUNCTION_P (fn1))
    return decls_match (fn1, fn2);
  return fn1 == fn2;
}
