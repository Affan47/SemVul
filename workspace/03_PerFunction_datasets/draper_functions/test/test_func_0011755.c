BuildVoronoiPolys(vtkUnstructuredGrid* input, vtkCellArray* voronoiPolys)
{
  bool boundaryTetra;
  vtkIdType npts, *pts;
  pts = NULL;
  vtkIdType neighborTetraId;
  vtkIdType i, k, h;
  vtkCellArray* edgeArray;
  vtkIdList* polyIds;
  vtkIdList* neighborCells;
  vtkIdList* neighborTrianglePointIds;
  vtkIdList* neighborNeighborCells;
  vtkIdList* linePointIds;
  vtkTetra* neighborTetra;

  edgeArray = vtkCellArray::New();
  polyIds = vtkIdList::New();
  neighborCells = vtkIdList::New();
  neighborTrianglePointIds = vtkIdList::New();
  neighborNeighborCells = vtkIdList::New();
  linePointIds = vtkIdList::New();

  this->ExtractUniqueEdges(input,edgeArray);

  edgeArray->InitTraversal();
  for (i=0; i<edgeArray->GetNumberOfCells(); i++)
    {
    edgeArray->GetNextCell(npts,pts);
    linePointIds->Initialize();
    linePointIds->InsertNextId(pts[0]);
    linePointIds->InsertNextId(pts[1]);

    boundaryTetra = false;
    neighborCells->Initialize();
    neighborTrianglePointIds->Initialize();
    polyIds->Initialize();
    input->GetCellNeighbors(-1,linePointIds,neighborCells);

    neighborTrianglePointIds->InsertNextId(linePointIds->GetId(0));
    neighborTrianglePointIds->InsertNextId(linePointIds->GetId(1));

    neighborTetraId = neighborCells->GetId(0);
    neighborTetra = vtkTetra::SafeDownCast(input->GetCell(neighborTetraId));
    polyIds->InsertNextId(neighborTetraId);
    for (k=0; k<neighborCells->GetNumberOfIds(); k++)
      {
      neighborNeighborCells->Initialize();
      for (h=0; h<neighborTetra->GetNumberOfPoints(); h++)
        {
        if (neighborTrianglePointIds->IsId(neighborTetra->GetPointId(h))==-1)
          {
          neighborTrianglePointIds->InsertId(2,neighborTetra->GetPointId(h));
          input->GetCellNeighbors(neighborTetraId,neighborTrianglePointIds,neighborNeighborCells);
          if (neighborNeighborCells->GetNumberOfIds()==0)
            {
            boundaryTetra = true;
            break;
            }
          else if (neighborNeighborCells->GetNumberOfIds()==1)
            {
            neighborTetraId = neighborNeighborCells->GetId(0);
            neighborTetra = vtkTetra::SafeDownCast(input->GetCell(neighborTetraId));
            polyIds->InsertUniqueId(neighborTetraId);
            break;
            }
          }
        }
      if (boundaryTetra)
        break;
      }
    if (!boundaryTetra)
      voronoiPolys->InsertNextCell(polyIds);
    }

  edgeArray->Delete();
  polyIds->Delete();
  neighborCells->Delete();
  neighborTrianglePointIds->Delete();
  neighborNeighborCells->Delete();
  linePointIds->Delete();
}
