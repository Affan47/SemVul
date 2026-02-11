cp_eh_personality (void)
{
  if (!cp_eh_personality_decl)
    {
      const char *lang = (pragma_java_exceptions ? "gcj" : "gxx");
      cp_eh_personality_decl = build_personality_function (lang);
    }

  return cp_eh_personality_decl;
}
