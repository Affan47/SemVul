RequestData(
                                  vtkInformation* vtkNotUsed(request),
                                  vtkInformationVector** inputVector,
                                  vtkInformationVector* outputVector )
{
  vtkInformation* inInfo  = inputVector[0]->GetInformationObject( 0 );
  vtkInformation* outInfo = outputVector->GetInformationObject( 0 );
  assert( inInfo  != NULL );
  assert( outInfo != NULL );

   vtkImageData* img = vtkImageData::SafeDownCast(
       inInfo->Get(vtkImageData::DATA_OBJECT() ) );
   assert( img != NULL );

   vtkStructuredGrid* grid = vtkStructuredGrid::SafeDownCast(
       outInfo->Get( vtkStructuredGrid::DATA_OBJECT()  ) );
   assert( grid != NULL );

   int dims[3];
   img->GetDimensions( dims );

   vtkPoints *gridPoints = vtkPoints::New();
   assert( gridPoints != NULL );
   gridPoints->SetDataTypeToDouble();
   gridPoints->SetNumberOfPoints( img->GetNumberOfPoints() );

   double pnt[3];
   for( int i=0; i < img->GetNumberOfPoints(); ++i )
   {
    img->GetPoint( i, pnt );
    gridPoints->SetPoint(i,pnt);
   }
   grid->SetDimensions(dims);
   grid->SetPoints( gridPoints );
   gridPoints->Delete();

   this->CopyPointData( img, grid );
   this->CopyCellData( img, grid );

   return 1;
}
