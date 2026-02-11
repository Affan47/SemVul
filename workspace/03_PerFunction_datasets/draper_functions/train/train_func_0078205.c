member(release r) const
{
  const release_list::size_type len = l.length();
  for(release_list::size_type i=0; i<len; i++)
    {
      if (l[i] == r)
	return true;
    }
  return false;
}
