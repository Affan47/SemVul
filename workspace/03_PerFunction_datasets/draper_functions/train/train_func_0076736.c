general_numcompare (char const *sa, char const *sb)
{


  char *ea;
  char *eb;
  long_double a = strtold (sa, &ea);
  long_double b = strtold (sb, &eb);


  if (sa == ea)
    return sb == eb ? 0 : -1;
  if (sb == eb)
    return 1;


  return (a < b ? -1
          : a > b ? 1
          : a == b ? 0
          : b == b ? -1
          : a == a ? 1
          : nan_compare (sa, sb));
}
