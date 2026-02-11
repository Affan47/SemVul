Next()
{
  Internal::IteratorVector::size_type numIterators = this->Implementation->Iterators.size();
  Internal::IteratorVector::size_type numTried = 0;
  vtkLabelHierarchyIterator* iter = this->Implementation->Iterators[this->Implementation->CurrentIterator].first;
  int count = this->Implementation->Iterators[this->Implementation->CurrentIterator].second;
  while (numTried <= numIterators && (iter->IsAtEnd() || this->Implementation->CurrentCount >= count))
    {
    this->Implementation->CurrentCount = 0;
    this->Implementation->CurrentIterator = (this->Implementation->CurrentIterator + 1) % numIterators;
    iter = this->Implementation->Iterators[this->Implementation->CurrentIterator].first;
    count = this->Implementation->Iterators[this->Implementation->CurrentIterator].second;
    if (!iter->IsAtEnd())
      {

      if (this->Implementation->InitialTraversal < this->Implementation->CurrentIterator)
        {
        this->Implementation->InitialTraversal = this->Implementation->CurrentIterator;
        }
      else
        {
        iter->Next();
        }
      }
    ++numTried;
    }
  this->Implementation->CurrentCount++;
  if (numTried > numIterators)
    {

    this->Implementation->CurrentIterator = numIterators;
    }
}
