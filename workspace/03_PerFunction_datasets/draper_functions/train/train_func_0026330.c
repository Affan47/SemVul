ShallowCopy(vtkSelectionNode* input)
{
  if (!input)
    {
    return;
    }
  this->Initialize();
  this->Properties->Copy(input->Properties, 0);
  this->SelectionData->ShallowCopy(input->SelectionData);
  this->SetQueryString(input->GetQueryString());
  this->Modified();
}
