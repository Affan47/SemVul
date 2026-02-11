is_call_dce_candidate (gimple call)
{
  tree fn;
  enum built_in_function fnc;


  if (gimple_call_lhs (call))
    return false;

  fn = gimple_call_fndecl (call);
  if (!fn
      || !DECL_BUILT_IN (fn)
      || (DECL_BUILT_IN_CLASS (fn) != BUILT_IN_NORMAL))
    return false;

  fnc = DECL_FUNCTION_CODE (fn);
  switch (fnc)
    {

    CASE_FLT_FN (BUILT_IN_ACOS):
    CASE_FLT_FN (BUILT_IN_ASIN):

    CASE_FLT_FN (BUILT_IN_ACOSH):
    CASE_FLT_FN (BUILT_IN_ATANH):
    CASE_FLT_FN (BUILT_IN_COSH):
    CASE_FLT_FN (BUILT_IN_SINH):

    CASE_FLT_FN (BUILT_IN_LOG):
    CASE_FLT_FN (BUILT_IN_LOG2):
    CASE_FLT_FN (BUILT_IN_LOG10):
    CASE_FLT_FN (BUILT_IN_LOG1P):

    CASE_FLT_FN (BUILT_IN_EXP):
    CASE_FLT_FN (BUILT_IN_EXP2):
    CASE_FLT_FN (BUILT_IN_EXP10):
    CASE_FLT_FN (BUILT_IN_EXPM1):
    CASE_FLT_FN (BUILT_IN_POW10):

    CASE_FLT_FN (BUILT_IN_SQRT):
      return check_builtin_call (call);

    case BUILT_IN_POW:
      return check_pow (call);
    default:
      break;
    }

  return false;
}
