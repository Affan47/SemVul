ComputeInterpolationWeights(
  double x[3], vtkPoints *pts, vtkCellArray *cells, double *weights)
{

  if ( !cells )
    {
    vtkGenericWarningMacro("Did not provide cells");
    return;
    }


  bool isATriangleMesh = true;
  if (cells->GetMaxCellSize() != 3)
    {
    isATriangleMesh = false;
    }
  else
    {
    vtkIdType npts;
    vtkIdType* pids;
    for (cells->InitTraversal(); cells->GetNextCell(npts,pids);)
      {
      if (npts != 3)
        {
        isATriangleMesh = false;
        break;
        }
      }
    }

  vtkIdType *t = cells->GetPointer();

  if (isATriangleMesh)
    {

    vtkMVCTriIterator iter(cells->GetNumberOfConnectivityEntries(), 4, t);

    vtkMeanValueCoordinatesInterpolator::
      ComputeInterpolationWeightsForTriangleMesh(x,pts,iter,weights);
    }
  else
    {
    vtkMVCPolyIterator iter(cells->GetNumberOfCells(), cells->GetMaxCellSize(), t);

    vtkMeanValueCoordinatesInterpolator::
      ComputeInterpolationWeightsForPolygonMesh(x,pts,iter,weights);
    }

  return;
}
