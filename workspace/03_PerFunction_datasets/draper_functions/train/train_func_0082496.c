FindClosestPoint
  ( const double x[3], double * miniDist2 )
{
  this->BuildLocator();


  *miniDist2 = this->OctreeMaxDimSize * this->OctreeMaxDimSize * 4.0;
  if ( this->OctreeRootNode == NULL ||
       this->OctreeRootNode->GetNumberOfPoints() == 0
     )
    {
    return -1;
    }

  double    elseDist2;
  vtkIdType elsePntId;
  vtkIdType pointIndx = -1;
  vtkIncrementalOctreeNode * pLeafNode = NULL;

  if (  this->OctreeRootNode->ContainsPoint( x )  )
    {
    pLeafNode = this->GetLeafContainer( this->OctreeRootNode, x );
    pointIndx = this->FindClosestPointInLeafNode( pLeafNode, x, miniDist2 );

    if (  ( *miniDist2 )  >  0.0  )
      {
      if (   pLeafNode->GetDistance2ToInnerBoundary( x, this->OctreeRootNode )
           < ( *miniDist2 )
         )
        {
        elsePntId = this->FindClosestPointInSphereWithoutTolerance
                          ( x, *miniDist2, pLeafNode, &elseDist2 );
        if (  elseDist2  <  ( *miniDist2)  )
          {
          pointIndx  = elsePntId;
          *miniDist2 = elseDist2;
          }
        }
      }
    }
  else
    {
    double   initialPt[3];
    double * minBounds = this->OctreeRootNode->GetMinBounds();
    double * maxBounds = this->OctreeRootNode->GetMaxBounds();
    this->OctreeRootNode->GetDistance2ToBoundary
                          ( x, initialPt, this->OctreeRootNode, 1 );


    if ( initialPt[0] <= minBounds[0] )
      {
      initialPt[0] = minBounds[0] + this->FudgeFactor;
      }
    else
    if ( initialPt[0] >= maxBounds[0] )
      {
      initialPt[0] = maxBounds[0] - this->FudgeFactor;
      }

    if ( initialPt[1] <= minBounds[1] )
      {
      initialPt[1] = minBounds[1] + this->FudgeFactor;
      }
    else
    if ( initialPt[1] >= maxBounds[1] )
      {
      initialPt[1] = maxBounds[1] - this->FudgeFactor;
      }

    if ( initialPt[2] <= minBounds[2] )
      {
      initialPt[2] = minBounds[2] + this->FudgeFactor;
      }
    else
    if ( initialPt[2] >= maxBounds[2] )
      {
      initialPt[2] = maxBounds[2] - this->FudgeFactor;
      }

    pLeafNode = this->GetLeafContainer( this->OctreeRootNode, initialPt );
    pointIndx = this->FindClosestPointInLeafNode( pLeafNode, x, miniDist2 );
    elsePntId = this->FindClosestPointInSphereWithoutTolerance
                      ( x, *miniDist2,  pLeafNode, &elseDist2 );

    if (  elseDist2  <  ( *miniDist2 )  )
      {
      pointIndx  = elsePntId;
      *miniDist2 = elseDist2;
      }

    minBounds = maxBounds = NULL;
    }

  pLeafNode = NULL;
  return pointIndx;
}
