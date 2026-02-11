print_protocols (struct protoent *proto)
{
  unsigned int i;

  printf ("%-21s %d", proto->p_name, proto->p_proto);

  i = 0;
  while (proto->p_aliases[i] != NULL)
    {
      putchar_unlocked (' ');
      fputs_unlocked (proto->p_aliases[i], stdout);
      ++i;
    }
  putchar_unlocked ('\n');
}
