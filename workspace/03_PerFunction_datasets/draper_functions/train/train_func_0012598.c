handle_starttag(void *clientdata, string name, pairlist attribs)
{
  if (in_text) {putchar('\n'); in_text = false;}
  print_attrs(attribs);
  if (linenumbering) printf("L%d\n", lineno);
  putchar('(');
  printf("%s", name);
  putchar('\n');
}
