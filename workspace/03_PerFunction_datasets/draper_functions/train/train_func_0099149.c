top_down_code (NODE_T * code_p)
{
  NODE_T *edoc_p = top_down_series (NEXT (code_p));
  if (edoc_p == NO_NODE || ISNT (edoc_p, EDOC_SYMBOL)) {
    diagnostic_node (A68_SYNTAX_ERROR, code_p, ERROR_KEYWORD);
    longjmp (top_down_crash_exit, 1);
    return (NO_NODE);
  } else {
    make_sub (code_p, edoc_p, CODE_SYMBOL);
    return (NEXT (code_p));
  }
}
