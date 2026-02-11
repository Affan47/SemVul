SetCenter( double _arg1, double _arg2, double _arg3 )
{
  if (  (this->Center[0] != _arg1)
      ||(this->Center[1] != _arg2)
      ||(this->Center[2] != _arg3))
    {


    if (this->Image)
      {
      double bounds[6];
      this->Image->GetBounds(bounds);
      if (_arg1 < bounds[0] || _arg1 > bounds[1] ||
          _arg2 < bounds[2] || _arg2 > bounds[3] ||
          _arg3 < bounds[4] || _arg3 > bounds[5])
        {
        return;
        }
      }

    this->Center[0] = _arg1;
    this->Center[1] = _arg2;
    this->Center[2] = _arg3;
    this->Modified();

    this->GetPlane(0)->SetOrigin(this->Center);
    this->GetPlane(1)->SetOrigin(this->Center);
    this->GetPlane(2)->SetOrigin(this->Center);
    }
}
