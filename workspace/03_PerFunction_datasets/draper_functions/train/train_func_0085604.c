print_flag(FILE *out, const mystring &s)
{
  if (s.empty())
    fputs("none", out);
  else
    fputs(s.c_str(), out);
}
