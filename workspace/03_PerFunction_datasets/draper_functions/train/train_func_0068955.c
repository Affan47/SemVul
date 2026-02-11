vtkGetSetPixelsFunc(
  void (**setpixels)(void *&out, const void *in, int numscalars, int n),
  int dataType, int dataSize, int numscalars, void *dataPtr)
{

  if (vtkImageReslicePointerAlignment(dataPtr, 4) &&
      ((dataSize*numscalars) & 0x03) == 0 &&
      dataSize < 4 && dataSize*numscalars <= 16)
    {
    switch ((dataSize*numscalars) >> 2)
      {
      case 1:
        *setpixels = &vtkImageResliceSetPixels<vtkTypeInt32>::Set1;
        break;
      case 2:
        *setpixels = &vtkImageResliceSetPixels<vtkTypeInt32>::Set2;
        break;
      case 3:
        *setpixels = &vtkImageResliceSetPixels<vtkTypeInt32>::Set3;
        break;
      case 4:
        *setpixels = &vtkImageResliceSetPixels<vtkTypeInt32>::Set4;
        break;
      }
    return;
    }

  switch (numscalars)
    {
    case 1:
      switch (dataType)
        {
        vtkTemplateAliasMacro(
          *setpixels = &vtkImageResliceSetPixels<VTK_TT>::Set1
          );
        default:
          *setpixels = 0;
        }
    case 2:
      switch (dataType)
        {
        vtkTemplateAliasMacro(
          *setpixels = &vtkImageResliceSetPixels<VTK_TT>::Set2
          );
        default:
          *setpixels = 0;
        }
    case 3:
      switch (dataType)
        {
        vtkTemplateAliasMacro(
          *setpixels = &vtkImageResliceSetPixels<VTK_TT>::Set3
          );
        default:
          *setpixels = 0;
        }
    case 4:
      switch (dataType)
        {
        vtkTemplateAliasMacro(
          *setpixels = &vtkImageResliceSetPixels<VTK_TT>::Set4
          );
        default:
          *setpixels = 0;
        }
    default:
      switch (dataType)
        {
        vtkTemplateAliasMacro(
          *setpixels = &vtkImageResliceSetPixels<VTK_TT>::Set
          );
        default:
          *setpixels = 0;
        }
    }
}
