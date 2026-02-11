CheckEdge(vtkIdType ptId, double x[3], vtkIdType p1,
                              vtkIdType p2, vtkIdType tri)
{
  int i;
  vtkIdType *pts, npts, numNei, nei, p3;
  double x1[3], x2[3], x3[3];
  vtkIdList *neighbors;
  vtkIdType swapTri[3];

  this->GetPoint(p1,x1);
  this->GetPoint(p2,x2);

  neighbors = vtkIdList::New();
  neighbors->Allocate(2);

  this->Mesh->GetCellEdgeNeighbors(tri,p1,p2,neighbors);
  numNei = neighbors->GetNumberOfIds();

  if ( numNei > 0 )
    {

    nei = neighbors->GetId(0);
    this->Mesh->GetCellPoints(nei, npts, pts);
    for (i=0; i<2; i++)
      {
      if ( pts[i] != p1 && pts[i] != p2 )
        {
        break;
        }
      }
    p3 = pts[i];
    this->GetPoint(p3,x3);


    if ( this->InCircle (x3, x, x1, x2) )
      {
      this->Mesh->RemoveReferenceToCell(p1,tri);
      this->Mesh->RemoveReferenceToCell(p2,nei);
      this->Mesh->ResizeCellList(ptId,1);
      this->Mesh->AddReferenceToCell(ptId,nei);
      this->Mesh->ResizeCellList(p3,1);
      this->Mesh->AddReferenceToCell(p3,tri);

      swapTri[0] = ptId; swapTri[1] = p3; swapTri[2] = p2;
      this->Mesh->ReplaceCell(tri,3,swapTri);

      swapTri[0] = ptId; swapTri[1] = p1; swapTri[2] = p3;
      this->Mesh->ReplaceCell(nei,3,swapTri);


      this->CheckEdge(ptId, x, p3, p2, tri);
      this->CheckEdge(ptId, x, p1, p3, nei);

      }
    }

  neighbors->Delete();
}
