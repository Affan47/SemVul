getLinesAsSet()
{
  std::map<int, ArLineFinderSegment*> *lines = getLines();
  std::set<ArLineFinderSegment*> lineSegPtrs;
  for(std::map<int, ArLineFinderSegment*>::const_iterator i = lines->begin(); i != lines->end(); ++i)
  {
    lineSegPtrs.insert( (*i).second );
  }
  return lineSegPtrs;
}
