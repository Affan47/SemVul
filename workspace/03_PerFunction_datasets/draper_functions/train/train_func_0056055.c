DeleteOwnLODs()
{
  if (this->MediumMapper == NULL)
    {
    return;
    }


  this->LODMappers->RemoveItem(this->LowMapper);
  this->LODMappers->RemoveItem(this->MediumMapper);


  this->SetLowResFilter(NULL);
  this->SetMediumResFilter(NULL);
  this->LowMapper->Delete();
  this->LowMapper = NULL;
  this->MediumMapper->Delete();
  this->MediumMapper = NULL;
}
