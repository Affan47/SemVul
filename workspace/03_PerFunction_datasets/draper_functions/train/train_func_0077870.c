rs6000_define_or_undefine_macro (bool define_p, const char *name)
{
  if (TARGET_DEBUG_BUILTIN || TARGET_DEBUG_TARGET)
    fprintf (stderr, "#%s %s\n", (define_p) ? "define" : "undef", name);

  if (define_p)
    cpp_define (parse_in, name);
  else
    cpp_undef (parse_in, name);
}
