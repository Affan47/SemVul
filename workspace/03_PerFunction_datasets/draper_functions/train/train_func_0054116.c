imCounterBegin(const char* title)
{
  static int first = 1;
  if (first)
  {
    memset(iCounterList, 0, MAX_COUNTERS*sizeof(iCounter));
    first = 0;
  }

  if (!iCounterFunc)
    return -1;

  int counter = -1;
  for (int i = 0; i < MAX_COUNTERS; i++)
  {
    if (iCounterList[i].sequence == 0 ||
        iCounterList[i].current == 0)
    {
      counter = i;
      break;
    }
  }

  if (counter == -1)
    return -1;

  iCounter *ct = &iCounterList[counter];

  ct->sequence++;

  if (ct->sequence == 1)
    iCounterFunc(counter, iCounterUserData, title, -1);

  return counter;
}
