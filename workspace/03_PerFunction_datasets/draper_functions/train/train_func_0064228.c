ThreadedExecute (vtkImageData *inData,
                                        vtkImageData *outData,
                                        int outExt[6], int id)
{

  if (inData->GetScalarType() != outData->GetScalarType())
    {
    vtkErrorMacro(<< "Execute: input ScalarType, "
                  << inData->GetScalarType()
                  << ", must match out ScalarType "
                  << outData->GetScalarType());
    return;
    }

  switch (inData->GetScalarType())
    {
    case VTK_INT:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<int *>(0));
      break;
    case VTK_UNSIGNED_INT:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<unsigned int *>(0));
      break;
    case VTK_LONG:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<long *>(0));
      break;
    case VTK_UNSIGNED_LONG:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<unsigned long *>(0));
      break;
    case VTK_SHORT:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<short *>(0));
      break;
    case VTK_UNSIGNED_SHORT:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<unsigned short *>(0));
      break;
    case VTK_CHAR:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<char *>(0));
      break;
    case VTK_UNSIGNED_CHAR:
      vtkImageMaskBitsExecute(this, inData, outData, outExt, id,
                              static_cast<unsigned char *>(0));
      break;
    default:
      vtkErrorMacro(<< "Execute: ScalarType can only be [unsigned] char, [unsigned] short, "
      << "[unsigned] int, or [unsigned] long.");
      return;
    }
}
