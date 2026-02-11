PrepareForRendering(vtkRenderer* renderer,
  vtkActor* actor)
{
  vtkDataObject* input = this->GetInput();
  if (!input)
    {
    vtkErrorMacro("No input present.");
    return;
    }


  if (!this->OutputData ||
    !this->OutputData->IsA(input->GetClassName()) ||
    this->OutputUpdateTime < this->MTime ||
    this->OutputUpdateTime < this->GetInput()->GetMTime())
    {
    if (this->OutputData)
      {
      this->OutputData->Delete();
      this->OutputData = 0;
      }

    this->OutputData = this->NewClone(input);
    this->OutputUpdateTime.Modified();
    }

  if (!this->ScalarVisibility)
    {

    this->ColorTextureMap = 0;
    this->Superclass::PrepareForRendering(renderer, actor);
    return;
    }


  this->ScalarsLookupTable = 0;
  int useTexture = this->CanUseTextureMapForColoring(input);
  if (useTexture)
    {


    this->UpdateColorTextureMap(actor->GetProperty()->GetOpacity(),
          this->GetPremultiplyColorsWithAlpha(actor));
    }
  else
    {

    this->ColorTextureMap = 0;
    }

  this->UsingScalarColoring = 0;


  if (input->IsA("vtkCompositeDataSet"))
    {
    vtkCompositeDataSet* cdInput = vtkCompositeDataSet::SafeDownCast(input);
    vtkCompositeDataSet* cdOutput =
      vtkCompositeDataSet::SafeDownCast(this->OutputData);
    vtkCompositeDataIterator* iter = cdInput->NewIterator();
    for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
      iter->GoToNextItem())
      {
      vtkDataSet* pdInput = vtkDataSet::SafeDownCast(
        iter->GetCurrentDataObject());
      vtkDataSet* pdOutput = vtkDataSet::SafeDownCast(
        cdOutput->GetDataSet(iter));
      if (pdInput && pdOutput)
        {
        this->MapScalars(pdOutput, actor->GetProperty()->GetOpacity(),
          this->GetPremultiplyColorsWithAlpha(actor),
          pdInput);
        }
      }

    iter->Delete();
    }
  else
    {
    this->MapScalars(vtkDataSet::SafeDownCast(this->OutputData),
      actor->GetProperty()->GetOpacity(),
      this->GetPremultiplyColorsWithAlpha(actor),
      vtkDataSet::SafeDownCast(input));
    }
  this->LastUsedAlpha = actor->GetProperty()->GetOpacity();
  this->LastUsedMultiplyWithAlpha = this->GetPremultiplyColorsWithAlpha(actor);
  this->Superclass::PrepareForRendering(renderer, actor);
}
