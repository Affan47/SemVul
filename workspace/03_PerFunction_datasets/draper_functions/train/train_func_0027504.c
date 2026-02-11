sort_patterndata(int start, int end)
{
  int div;

  if (start < end)
  {
    div = divide(start, end);
    sort_patterndata(start, div - 1);
    sort_patterndata(div + 1, end);
  }
}
