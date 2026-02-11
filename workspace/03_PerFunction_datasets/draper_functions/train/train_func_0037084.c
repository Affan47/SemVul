InsertPoint(vtkIdType ptId, double point[3])
{
  vtkIdType pos = this->HashFunction(ptId);


  assert("check: valid range pos" &&
         static_cast<unsigned>(pos) < this->HashPoints->PointVector.size() );


  vtkEdgeTablePoints::VectorPointTableType &vect =
    this->HashPoints->PointVector[pos];


  PointEntry newEntry(this->NumberOfComponents);
  newEntry.PointId = ptId;
  memcpy(newEntry.Coord,point,sizeof(double)*3);
  newEntry.Reference = 1;


  vect.push_back( newEntry );
}
