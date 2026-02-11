SetPointArrayStatus(const char* name, int flag)
{
  if(this->MetaData->GetNumberOfPointArrays()==0)
    {


    this->MetaData->SetPointArrayInitStatus(name, flag);
    }

  this->MetaData->SetPointArrayStatus(name, flag);
  this->Modified();
}
