CellBoundary(int subId, double pcoords[3],
                                    vtkIdList *pts)
{


  vtkIdType pntIndx;
  for ( int i = 0; i < 4; i ++ )
    {
    pntIndx = this->PointIds
                  ->GetId(  this->TetraIds->GetId( (subId << 2) + i )  );
    this->Tetra->PointIds->SetId( i, pntIndx );
    this->Tetra->Points
        ->SetPoint(  i,  this->TetraPoints->GetPoint( (subId << 2) + i )  );
    }


  return this->Tetra->CellBoundary( subId, pcoords, pts );
}
