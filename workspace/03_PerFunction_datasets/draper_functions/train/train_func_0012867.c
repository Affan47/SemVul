GetAllTags(const ERootType& inRootType) const
{
  std::vector<Tag> theReturn = GetRequiredTags(inRootType);
  std::vector<Tag> theNext = GetUniqueTags(inRootType);
  theReturn.insert(theReturn.end(), theNext.begin(), theNext.end());
  theNext = GetOptionalTags(inRootType);
  theReturn.insert(theReturn.end(), theNext.begin(), theNext.end());
  return theReturn;
}
