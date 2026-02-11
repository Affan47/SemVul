SetTableRange(double rmin, double rmax)
{
  if (this->Scale == VTK_SCALE_LOG10 &&
      ((rmin > 0 && rmax < 0) || (rmin < 0 && rmax > 0)))
    {
    vtkErrorMacro("Bad table range for log scale: ["<<rmin<<", "<<rmax<<"]");
    return;
    }
  if (rmax < rmin)
    {
    vtkErrorMacro("Bad table range: ["<<rmin<<", "<<rmax<<"]");
    return;
    }

  if (this->TableRange[0] == rmin && this->TableRange[1] == rmax)
    {
    return;
    }

  this->TableRange[0] = rmin;
  this->TableRange[1] = rmax;

  this->Modified();
}
