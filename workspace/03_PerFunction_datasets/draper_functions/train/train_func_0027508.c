uses_int_iterator_p (rtx x, struct mapping *iterator, int opno)
{
  int i;
  for (i=0; i < num_int_iterator_data; i++)
    if (int_iterator_data[i].iterator->group == iterator->group &&
	int_iterator_data[i].iterator->index == iterator->index)
      {

	struct int_iterator_mapping it = int_iterator_data[i];
	int j;

	for (j=0; j < it.num_rtx; j++)
	{
	  if (it.rtxs[j].x == x && it.rtxs[j].opno == opno)
	    return true;
	}
      }
  return false;
}
