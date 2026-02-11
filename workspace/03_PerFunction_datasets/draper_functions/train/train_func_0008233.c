GetComputedViewportValue(vtkViewport* viewport)
{
  double *f = this->GetComputedDoubleViewportValue(viewport);

  this->ComputedViewportValue[0] = static_cast<int>(VTK_RINT(f[0]));
  this->ComputedViewportValue[1] = static_cast<int>(VTK_RINT(f[1]));

  return this->ComputedViewportValue;
}
