go_output_type (struct godump_container *container)
{
  struct obstack *ob;

  ob = &container->type_obstack;
  obstack_1grow (ob, '\0');
  fputs (obstack_base (ob), go_dump_file);
  obstack_free (ob, obstack_base (ob));
}
