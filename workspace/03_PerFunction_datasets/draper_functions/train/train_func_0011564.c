AppendDifferentPoints(vtkDataArray *dest,
                                              vtkDataArray *src,
                                              vtkIdType offset)
{
  float  *fSrc;
  double *dSrc, *dDest;
  vtkIdType p;

  if (src->GetNumberOfTuples() + offset > dest->GetNumberOfTuples())
    {
    vtkErrorMacro("Destination not big enough");
    return;
    }

  vtkIdType vals = src->GetMaxId()+1;
  switch (dest->GetDataType())
    {


    case VTK_FLOAT:
        vtkErrorMacro("Dest type should be double? "
            << dest->GetDataType());
        break;


    case VTK_DOUBLE:
      dDest = static_cast<double*>(
        dest->GetVoidPointer(offset*src->GetNumberOfComponents()));

      switch (src->GetDataType())
        {
        case VTK_FLOAT:
          fSrc = static_cast<float*>(src->GetVoidPointer(0));
          for (p=0; p<vals; p++)
            {
            dDest[p] = static_cast<double>(fSrc[p]);
            }
          break;
        case VTK_DOUBLE:
          dSrc = static_cast<double*>(src->GetVoidPointer(0));
          memcpy(dDest, dSrc, vals*sizeof(double));
          break;
        default:
          vtkErrorMacro("Unknown data type " << dest->GetDataType());
        }
      break;

    default:
      vtkErrorMacro("Unknown data type " << dest->GetDataType());
    }

}
