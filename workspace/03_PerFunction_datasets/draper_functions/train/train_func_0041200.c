MusterIdx(const Title name, const int nth)
{
  int i, count = 0;

  for (i = 0; i != name && i < TITLES; ++i)
    count += titleCount[i];

  if (i == TITLES)
    return 47;


  if (nth < titleCount[name])
    {
      return count + nth;
    }

  return 47;
}
