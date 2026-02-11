handle_pragma_java_exceptions (cpp_reader* )
{
  tree x;
  if (pragma_lex (&x) != CPP_EOF)
    warning (0, "junk at end of #pragma GCC java_exceptions");

  choose_personality_routine (lang_java);
  pragma_java_exceptions = true;
}
