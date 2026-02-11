parseGate (void)
{
  int ch;
 loop:
  while (isspace (ch = fgetc (stdin)));
  fputc (ch, stdout);
  switch (ch) {
  case 't':
  case 'f':
    return 0;
  case '|':
  case '&':
  case 'i':
  case 'e':
    if (parseGate ())
      return 1;
  case '!':
    goto loop;
  case 'p':
    if (1 != fscanf (stdin, "%d", &ch)) {
      fputs ("error in proposition number\n", stderr);
      return 1;
    }
    fprintf (stdout, "%d", ch);
    return 0;
  case EOF:
    fputs ("unexpected end of file while parsing formula\n", stderr);
    return 2;
  default:
    fprintf (stderr, "unknown character 0x%02x", ch);
    return 2;
  }
}
