SetInput(vtkLinearTransform *input)
{
  if (this->Input == input)
    {
    return;
    }
  if (input && input->CircuitCheck(this))
    {
    vtkErrorMacro("SetInput: this would create a circular reference.");
    return;
    }
  if (this->Input)
    {
    this->Input->Delete();
    }
  this->Input = input;
  if (this->Input)
    {
    this->Input->Register(this);
    }
  this->Modified();
}
