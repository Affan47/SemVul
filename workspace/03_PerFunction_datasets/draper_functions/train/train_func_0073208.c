tree_nca (int x, int y, int *parent, int *marks, int mark)
{
  if (x == -1 || x == y)
    return y;


  marks[x] = mark;
  marks[y] = mark;

  while (1)
    {
      x = parent[x];
      if (x == -1)
	break;
      if (marks[x] == mark)
	return x;
      marks[x] = mark;

      y = parent[y];
      if (y == -1)
	break;
      if (marks[y] == mark)
	return y;
      marks[y] = mark;
    }


  if (x == -1)
    {
      for (y = parent[y]; marks[y] != mark; y = parent[y])
	continue;

      return y;
    }
  else
    {
      for (x = parent[x]; marks[x] != mark; x = parent[x])
	continue;

      return x;
    }
}
