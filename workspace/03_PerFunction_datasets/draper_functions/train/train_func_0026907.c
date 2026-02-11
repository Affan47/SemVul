pack(int *ids)
{
  for (int n = 0; n < size_one; n++) (this->*pack_choice[n])(n);
  if (ids) {
    int *tag = atom->tag;
    for (int i = 0; i < nchoose; i++)
      ids[i] = tag[clist[i]];
  }
}
