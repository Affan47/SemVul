Triangulate(int vtkNotUsed(index), vtkIdList *ptIds,
                         vtkPoints *pts)
{
  double d1, d2;

  pts->Reset();
  ptIds->Reset();


  d1 = vtkMath::Distance2BetweenPoints(this->Points->GetPoint(0),
                                   this->Points->GetPoint(2));
  d2 = vtkMath::Distance2BetweenPoints(this->Points->GetPoint(1),
                                   this->Points->GetPoint(3));

  if ( d1 <= d2 )
    {
    ptIds->InsertId(0,this->PointIds->GetId(0));
    pts->InsertPoint(0,this->Points->GetPoint(0));
    ptIds->InsertId(1,this->PointIds->GetId(1));
    pts->InsertPoint(1,this->Points->GetPoint(1));
    ptIds->InsertId(2,this->PointIds->GetId(2));
    pts->InsertPoint(2,this->Points->GetPoint(2));

    ptIds->InsertId(3,this->PointIds->GetId(0));
    pts->InsertPoint(3,this->Points->GetPoint(0));
    ptIds->InsertId(4,this->PointIds->GetId(2));
    pts->InsertPoint(4,this->Points->GetPoint(2));
    ptIds->InsertId(5,this->PointIds->GetId(3));
    pts->InsertPoint(5,this->Points->GetPoint(3));
    }
  else
    {
    ptIds->InsertId(0,this->PointIds->GetId(0));
    pts->InsertPoint(0,this->Points->GetPoint(0));
    ptIds->InsertId(1,this->PointIds->GetId(1));
    pts->InsertPoint(1,this->Points->GetPoint(1));
    ptIds->InsertId(2,this->PointIds->GetId(3));
    pts->InsertPoint(2,this->Points->GetPoint(3));

    ptIds->InsertId(3,this->PointIds->GetId(1));
    pts->InsertPoint(3,this->Points->GetPoint(1));
    ptIds->InsertId(4,this->PointIds->GetId(2));
    pts->InsertPoint(4,this->Points->GetPoint(2));
    ptIds->InsertId(5,this->PointIds->GetId(3));
    pts->InsertPoint(5,this->Points->GetPoint(3));
    }

  return 1;
}
