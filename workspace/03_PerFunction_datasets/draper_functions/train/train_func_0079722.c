AddDataSet( vtkDataSet * dataset )
{
  if ( !dataset )
    {
    vtkErrorMacro( <<"Dataset NULL!" );
    return;
    }


  this->DataSets->push_back( dataset );


  vtkSmartPointer< vtkAbstractCellLocator > locator = 0;
  if (  dataset->IsA( "vtkPointSet" )  )
    {

    if ( !this->CellLocatorPrototype )
      {
      locator = vtkSmartPointer < vtkModifiedBSPTree >::New();
      }
    else
      {
      locator.TakeReference( this->CellLocatorPrototype->NewInstance() );
      }

    locator->SetLazyEvaluation( 1 );
    locator->SetDataSet( dataset );
    }
  this->CellLocators->push_back( locator );

  int  size = dataset->GetMaxCellSize();
  if ( size > this->WeightsSize )
    {
    this->WeightsSize = size;
    if ( this->Weights )
      {
      delete[] this->Weights;
      this->Weights = NULL;
      }
    this->Weights = new double[size];
    }
}
