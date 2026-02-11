Build()
  {
  if (this->PointIds && !this->ReallocateOnBuild)
    {
    return;
    }

  this->NPoints = 0;

  if (this->PointIds!=NULL)
    {
    delete[] this->PointIds;
    this->PointIds = NULL;
    }
  if (this->Weights!=NULL)
    {
    delete[] this->Weights;
    this->Weights = NULL;
    }
  if (this->CenterWeight!=NULL)
    {
    delete[] this->CenterWeight;
    this->CenterWeight = NULL;
    }
  }
