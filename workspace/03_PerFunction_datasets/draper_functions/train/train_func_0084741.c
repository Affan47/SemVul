print_c_name (lf *file, const char *name)
{
  int nr = 0;
  const char *pos;
  for (pos = name; *pos != '\0'; pos++)
    {
      switch (*pos)
	{
	case '/':
	case '-':
	  break;
	case ' ':
	case '.':
	  nr += lf_putchr (file, '_');
	  break;
	default:
	  nr += lf_putchr (file, *pos);
	  break;
	}
    }
  return nr;
}
