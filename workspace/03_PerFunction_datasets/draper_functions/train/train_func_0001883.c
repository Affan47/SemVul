print(FILE * out) const
{
  const release_list::size_type len = l.length();
  for(release_list::size_type i=0; i<len; i++)
    {
      if (i > 0)
	{
	  if (putc_failed(fputc(' ', out)))
	    return false;
	}

      if (l[i].print(out))
	return false;
    }
  return true;
}
