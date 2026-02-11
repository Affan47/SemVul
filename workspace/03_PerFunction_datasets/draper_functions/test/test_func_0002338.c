SetNumberOfIterations(int num)
{
  int temp;

  vtkDebugMacro(<< "SetNumberOfIterations: " << num);
  if (this->NumberOfIterations == num)
    {
    return;
    }

  this->Modified();
  temp = num*2 + 1;
  this->KernelSize[0] = temp;
  this->KernelSize[1] = temp;
  this->KernelMiddle[0] = num;
  this->KernelMiddle[1] = num;

  this->NumberOfIterations = num;
}
