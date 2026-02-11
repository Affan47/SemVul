ComputeSupportSize(
  const double matrix[16], int size[3])
{

  if (this->Antialiasing)
    {
    size[0] = VTK_SINC_KERNEL_SIZE_MAX;
    size[1] = VTK_SINC_KERNEL_SIZE_MAX;
    size[2] = VTK_SINC_KERNEL_SIZE_MAX;
    }
  else
    {
    for (int i = 0; i < 3; i++)
      {

      size[i] = 2*this->WindowHalfWidth;
      double rowscale = this->BlurFactors[i];
      if (rowscale > (1.0 + VTK_INTERPOLATE_FLOOR_TOL))
        {
        size[i] = 2*static_cast<int>(
        rowscale*this->WindowHalfWidth + 1.0 - VTK_INTERPOLATE_FLOOR_TOL);
        }
      }
    }

  if (matrix == NULL)
    {
    return;
    }

  if (this->Antialiasing)
    {

    this->BlurFactors[0] = 1.0;
    this->BlurFactors[1] = 1.0;
    this->BlurFactors[2] = 1.0;
    this->KernelSize[0] = 2*this->WindowHalfWidth;
    this->KernelSize[1] = 2*this->WindowHalfWidth;
    this->KernelSize[2] = 2*this->WindowHalfWidth;
    }
  else
    {

    this->KernelSize[0] = size[0];
    this->KernelSize[1] = size[1];
    this->KernelSize[2] = size[2];
    }


  if (matrix[12] != 0 || matrix[13] != 0 || matrix[14] != 0 ||
      matrix[15] != 1.0)
    {
    return;
    }


  for (int i = 0; i < 3; i++)
    {
    int integerRow = 1;
    double rowscale = 0.0;
    for (int j = 0; j < 3; j++)
      {

      double x = matrix[4*i + j];
      rowscale += x*x;


      double f;
      vtkInterpolationMath::Floor(x, f);
      integerRow &= (f == 0);
      }

    if (this->Antialiasing)
      {

      rowscale = sqrt(rowscale);
      }
    else
      {

      rowscale = this->BlurFactors[i];
      }


    if (rowscale > (1.0 + VTK_INTERPOLATE_FLOOR_TOL))
      {

      this->BlurFactors[i] = rowscale;
      int s = 2*static_cast<int>(
       rowscale*this->WindowHalfWidth + 1.0 - VTK_INTERPOLATE_FLOOR_TOL);
      size[i] = s;
      this->KernelSize[i] = s;
      }
    else if (integerRow)
      {

      size[i] = 1;
      }
    }


  this->InternalUpdate();
}
