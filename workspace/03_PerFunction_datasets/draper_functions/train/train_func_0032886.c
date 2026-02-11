get_one_normal_day (unsigned length)
{
  unsigned day;

  do
    {
      day = rand () % length;
    }
  while (day % WEEK >= SATURDAY);

  return day;
}
