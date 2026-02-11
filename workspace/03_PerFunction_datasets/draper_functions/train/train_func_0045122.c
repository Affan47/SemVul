usedSet(ISet<Char> &set) const
{
  for (size_t i = 0; i < sections_.size(); i++)
    sections_[i].usedSet(set);
}
