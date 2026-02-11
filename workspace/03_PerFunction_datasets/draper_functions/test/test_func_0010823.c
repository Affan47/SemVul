visu_node_array_iter_next2(VisuNodeArrayIter *iter1, VisuNodeArrayIter *iter2)
{
  if (!iter1->init)
    {
      visu_node_array_iterStart(iter1->array, iter1);
      visu_node_array_iterStart(iter1->array, iter2);
    }
  else
    {
      if (!iter1->node)
        return FALSE;


      visu_node_array_iterNext(iter1->array, iter2);
      if (!iter2->node ||
	  iter2->node->posElement > iter1->node->posElement ||
	  (iter2->node->posElement == iter1->node->posElement &&
	   iter2->node->posNode    >= iter1->node->posNode))
	{
	  visu_node_array_iterNext(iter1->array, iter1);
	  if (iter1->node)
	    visu_node_array_iterStart(iter1->array, iter2);
	  else
	    iter2->node = (VisuNode*)0;
	}

    }

  if (!iter1->node && !iter2->node)
    return FALSE;
  else
    return TRUE;
}
