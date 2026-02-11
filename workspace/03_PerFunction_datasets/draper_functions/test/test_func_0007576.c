InitPart(vtkStdString name,
                             const vtkIdType& partId,
                             const vtkIdType& userMatId,
                             const vtkIdType& numGlobalPoints,
                             const int& sizeOfWord)
{


  this->Name = name;
  this->PartId = partId;
  this->UserMaterialId = userMatId;
  this->DoubleBased = (sizeOfWord == 8);
  this->NumberOfGlobalPoints = numGlobalPoints;

  this->GlobalPointsUsed = NULL;

  this->Grid = vtkUnstructuredGrid::New();
  this->Points = vtkPoints::New();

  this->Grid->SetPoints(this->Points);


  vtkFieldData *fd = this->Grid->GetFieldData();

  vtkStringArray *partName = vtkStringArray::New();
  partName->SetName("Name");
  partName->SetNumberOfValues(1);
  partName->SetValue(0,this->Name);
  fd->AddArray(partName);
  partName->FastDelete();

  vtkStringArray *partType = vtkStringArray::New();
  partType->SetName("Type");
  partType->SetNumberOfValues(1);
  partType->SetValue(0,TypeNames[this->Type]);
  fd->AddArray(partType);
  partType->FastDelete();

  vtkIntArray *materialId = vtkIntArray::New();
  materialId->SetName("Material Id");
  materialId->SetNumberOfValues(1);
  materialId->SetValue(0,this->UserMaterialId);
  fd->AddArray(materialId);
  materialId->FastDelete();
}
