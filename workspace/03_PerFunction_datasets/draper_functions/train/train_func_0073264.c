Triangulate3DContour(vtkIdType npts, vtkIdType * pts,
                          vtkCellArray *cellArray)
{
  vtkIdType start = 0;
  vtkIdType end = npts-1;
  vtkIdType ids[3];

  while (start < end)
    {
    ids[0] = pts[start++];
    ids[1] = pts[start];
    ids[2] = pts[end];
    cellArray->InsertNextCell(3, ids);

    if (start >= end - 1)
      {
      return;
      }

    ids[0] = pts[end];
    ids[1] = pts[start];
    ids[2] = pts[--end];
    cellArray->InsertNextCell(3, ids);
    }
}
