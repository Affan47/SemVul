Trace(int X, int Y)
{
  if ( !this->PropPicker->PickProp(X,Y,this->CurrentRenderer) ){ return; }
  if ( this->ViewProp !=  this->PropPicker->GetViewProp() ){ return; }

  double pos[3];
  this->PropPicker->GetPickPosition(pos);

  if ( this->SnapToImage )
    {
    this->Snap(pos);
    }

  if ( this->ProjectToPlane )
    {
    pos[this->ProjectionNormal] = this->ProjectionPosition;
    }

  if (  this->LastX != X || this->LastY != Y )
    {
    if ( this->State == vtkImageTracerWidget::Tracing )
      {
      if ( this->NumberOfHandles == 1 )
        {
        this->AppendHandles(pos);
        }
      else
        {
        this->AdjustHandlePosition(this->CurrentHandleIndex,pos);
        }
      this->AppendLine(pos);
      }
    else if ( this->State == vtkImageTracerWidget::Snapping )
      {
      if ( this->IsSnapping != this->CurrentHandleIndex  )
        {
        this->AppendHandles(pos);
        this->AppendLine(pos);
        this->IsSnapping = this->CurrentHandleIndex;
        }
      else
        {
        this->AdjustHandlePosition(this->CurrentHandleIndex,pos);
        this->LinePoints->SetPoint(this->PickCount,pos);
        this->LinePoints->GetData()->Modified();
        this->LineData->Modified();
        }
      }
   }

  this->LastX = X;
  this->LastY = Y;
}
