getBodyElementLoopId(IdList* loop_ids, int& id, int& direction)
{


  int nof_ids = loop_ids->size();

  int* ids = new int[nof_ids];

  IdList::iterator pos = loop_ids->begin();

  int index = 0;
  while ( pos != loop_ids->end() ) {
    ids[index++] = *pos++;
  }

  return getBodyElementLoopId(nof_ids, ids, id, direction);

  delete[] ids;
}
