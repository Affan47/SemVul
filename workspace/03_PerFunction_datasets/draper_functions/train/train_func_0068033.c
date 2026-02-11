IsPointOccluded(
  const double x[3],
  const float *zPtr
  )
{
  double view[4];
  double dx[3], z;
  double xx[4] = {x[0], x[1], x[2], 1.0};

  this->CompositePerspectiveTransform->MultiplyPoint(xx, view);
  if (view[3] == 0.0)
    {
    return false;
    }
  this->Renderer->SetViewPoint(view[0]/view[3], view[1]/view[3], view[2]/view[3]);
  this->Renderer->ViewToDisplay();
  this->Renderer->GetDisplayPoint(dx);


  if ( dx[0] >= this->InternalSelection[0] && dx[0] <= this->InternalSelection[1] &&
    dx[1] >= this->InternalSelection[2] && dx[1] <= this->InternalSelection[3] )
    {
    if (zPtr != NULL)
      {


      z = zPtr[static_cast<int>(dx[0]) - this->InternalSelection[0]
      + (static_cast<int>(dx[1]) - this->InternalSelection[2])
        *(this->InternalSelection[1] - this->InternalSelection[0] + 1)];
      }
    else
      {
      z = this->Renderer->GetZ(static_cast<int>(dx[0]),
        static_cast<int>(dx[1]));
      }

    if( dx[2] < (z + this->Tolerance) )
      {
      return true;
      }
    }

  return false;
}
