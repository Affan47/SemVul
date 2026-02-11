inlist(mylist<mystring> l, const mystring& find)
{
  const mylist<mystring>::size_type len = l.length();
  for (mylist<mystring>::size_type i=0; i<len; ++i)
    {
      if (find == l[i])
	return true;
    }
  return false;
}
