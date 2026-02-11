Initialize()
{

  this->Superclass::Initialize();


  vtkDataSetAttributes *vertData = this->GetVertexData();
  vertData->AllocateArrays(1);


  vtkNew<vtkUnsignedShortArray> atomicNums;
  atomicNums->SetNumberOfComponents(1);
  atomicNums->SetName("Atomic Numbers");
  vertData->SetScalars(atomicNums.GetPointer());


  this->Points->Initialize();


  vtkDataSetAttributes *edgeData = this->GetEdgeData();
  edgeData->AllocateArrays(1);

  vtkNew<vtkUnsignedShortArray> bondOrders;
  bondOrders->SetNumberOfComponents(1);
  bondOrders->SetName("Bond Orders");
  edgeData->SetScalars(bondOrders.GetPointer());

  this->UpdateBondList();


  this->ElectronicData = NULL;

  this->Modified();
}
