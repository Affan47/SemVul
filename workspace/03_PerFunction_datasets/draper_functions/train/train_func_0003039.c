GetRefinementRatio(unsigned int level)
{
  if (!this->Superclass::HasChildMetaData(level))
    {
    return 0;
    }

  vtkInformation* info = this->Superclass::GetChildMetaData(level);
  if (!info)
    {
    return 0;
    }
  return info->Has(REFINEMENT_RATIO())? info->Get(REFINEMENT_RATIO()): 0;
}
