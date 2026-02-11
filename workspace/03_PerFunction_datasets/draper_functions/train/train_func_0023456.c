nodes_identical (d1, d2)
     struct decision *d1, *d2;
{
  struct decision_test *t1, *t2;

  for (t1 = d1->tests, t2 = d2->tests; t1 && t2; t1 = t1->next, t2 = t2->next)
    {
      if (t1->type != t2->type)
	return 0;
      if (! nodes_identical_1 (t1, t2))
	return 0;
    }


  if (t1 != t2)
    return 0;


  if (d1->success.first
      && d2->success.first
      && strcmp (d1->success.first->position, d2->success.first->position))
    return 0;

  return 1;
}
