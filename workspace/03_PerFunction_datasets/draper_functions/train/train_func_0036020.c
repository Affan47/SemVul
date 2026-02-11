GeneratePlaneOutline()
{
  vtkPoints* points   = vtkPoints::New(VTK_DOUBLE);
  points->SetNumberOfPoints(4);
  int i;
  for (i = 0; i < 4; i++)
    {
    points->SetPoint(i,0.0,0.0,0.0);
    }

  vtkCellArray *cells = vtkCellArray::New();
  cells->Allocate(cells->EstimateSize(4,2));
  vtkIdType pts[2];
  pts[0] = 3; pts[1] = 2;
  cells->InsertNextCell(2,pts);
  pts[0] = 0; pts[1] = 1;
  cells->InsertNextCell(2,pts);
  pts[0] = 0; pts[1] = 3;
  cells->InsertNextCell(2,pts);
  pts[0] = 1; pts[1] = 2;
  cells->InsertNextCell(2,pts);

  this->PlaneOutlinePolyData->SetPoints(points);
  points->Delete();
  this->PlaneOutlinePolyData->SetLines(cells);
  cells->Delete();

  vtkPolyDataMapper* planeOutlineMapper = vtkPolyDataMapper::New();
  planeOutlineMapper->SetInput( this->PlaneOutlinePolyData );
  planeOutlineMapper->SetResolveCoincidentTopologyToPolygonOffset();
  this->PlaneOutlineActor->SetMapper(planeOutlineMapper);
  this->PlaneOutlineActor->PickableOff();
  planeOutlineMapper->Delete();
}
