GetSelectionIdArray(vtkDataSet* input)
{
  if (this->UseSelectionIds)
    {
    int association = vtkDataObject::FIELD_ASSOCIATION_POINTS;
    vtkDataArray* arr = this->GetInputArrayToProcess(
          vtkGlyph3DMapper::SELECTIONID, input, association);
    return arr;
    }
  return NULL;
}
