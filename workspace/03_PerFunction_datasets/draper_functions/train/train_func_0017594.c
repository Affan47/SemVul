gencode ()
{
  const char **fmt;

  puts ("#include \"config.h\"");
  puts ("#include \"system.h\"");
  puts ("#include \"obstack.h\"");
  puts ("#include \"rtl.h\"");
  puts ("#include \"ggc.h\"\n");
  puts ("extern struct obstack *rtl_obstack;\n");

  for (fmt = formats; *fmt != 0; fmt++)
    gendef (*fmt);
}
