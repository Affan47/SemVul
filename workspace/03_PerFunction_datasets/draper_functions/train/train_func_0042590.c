purgeNameList(NameList& list)
{
  NameList::iterator pos = list.begin();
  NameList::iterator end_pos = list.end();

  while (pos != end_pos) {
    delete[] (*pos);
    pos++;
  }
  list.clear();
}
