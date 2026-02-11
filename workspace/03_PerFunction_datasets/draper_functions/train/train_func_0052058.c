FunctionValues(double* x, double* f)
{
  vtkGenericDataSet* ds;
  if(!this->LastDataSet && !this->DataSets->empty())
    {
    ds = (*this->DataSets)[0];
    this->LastDataSet = ds;
    }
  else
    {
    ds = this->LastDataSet;
    }
  int retVal = this->FunctionValues(ds, x, f);
  if (!retVal)
    {
    tmp_count = 0;
    for(DataSetsTypeBase::iterator i = this->DataSets->begin();
        i != this->DataSets->end(); ++i)
      {
      ds = *i;
      if(ds && ds != this->LastDataSet)
        {
        this->ClearLastCell();
        retVal = this->FunctionValues(ds, x, f);
        if (retVal)
          {
          this->LastDataSet = ds;
          return retVal;
          }
        }
      }
    this->ClearLastCell();
    return 0;
    }
  tmp_count++;
  return retVal;
}
