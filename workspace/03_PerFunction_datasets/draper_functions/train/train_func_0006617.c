BuildBlockAttributesIndex()
{
  int nblocks = this->NumberOfBlocks;
  int *nelts = this->BlockNumberOfElements;
  int *natts = this->BlockNumberOfAttributesPerElement;

  if ((nblocks < 1) || !nelts || !natts)
    {
    return 1;
    }

  if (this->BlockAttributesIndex)
    {
    delete [] this->BlockAttributesIndex;
    }

  this->BlockAttributesIndex = new int [nblocks];

  int idx = 0;

  for (int i=0; i<nblocks; i++)
    {
    this->BlockAttributesIndex[i] = idx;
    idx += (int)(nelts[i] * natts[i]);
    }

  this->SizeBlockAttributeArray = idx;

  return 0;
}
