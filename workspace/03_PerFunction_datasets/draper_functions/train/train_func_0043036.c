RemovePoint (double t)
{
  if ( this->ParametricRange[0] != this->ParametricRange[1] )
    {
    t = (t < this->ParametricRange[0] ? this->ParametricRange[0] :
         (t > this->ParametricRange[1] ? this->ParametricRange[1] : t));
    }
  this->PiecewiseFunction->RemovePoint (t);
}
