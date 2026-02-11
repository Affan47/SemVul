CompareAverageOfL2Norm(
        vtkDataArray *daA,
        vtkDataArray *daB,
        double tol)
{
  int typeA=daA->GetDataType();
  int typeB=daB->GetDataType();
  if (typeA!=typeB)
    {
    vtkWarningMacro("Incompatible data types: "
                    << typeA << ","
                    << typeB << ".");
    return 0;
    }

  vtkIdType nTupsA=daA->GetNumberOfTuples();
  vtkIdType nTupsB=daB->GetNumberOfTuples();
  int nCompsA=daA->GetNumberOfComponents();
  int nCompsB=daB->GetNumberOfComponents();

  if ((nTupsA!=nTupsB)
     || (nCompsA!=nCompsB))
    {
    vtkWarningMacro(
              "Arrays: " << daA->GetName()
              << " (nC=" << nCompsA
              << " nT= "<< nTupsA << ")"
              << " and " << daB->GetName()
              << " (nC=" << nCompsB
              << " nT= "<< nTupsB << ")"
              << " do not have the same structure.");
    return 0;
    }

  double L2=0.0;
  vtkIdType N=0;
  switch (typeA)
    {
    case VTK_DOUBLE:
      {
      vtkDoubleArray *A=vtkDoubleArray::SafeDownCast(daA);
      double *pA=A->GetPointer(0);
      vtkDoubleArray *B=vtkDoubleArray::SafeDownCast(daB);
      double *pB=B->GetPointer(0);
      N=AccumulateScaledL2Norm(pA,pB,nTupsA,nCompsA,L2);
      }
      break;
    case VTK_FLOAT:
      {
      vtkFloatArray *A=vtkFloatArray::SafeDownCast(daA);
      float *pA=A->GetPointer(0);
      vtkFloatArray *B=vtkFloatArray::SafeDownCast(daB);
      float *pB=B->GetPointer(0);
      N=AccumulateScaledL2Norm(pA,pB,nTupsA,nCompsA,L2);
      }
      break;
    default:
      if (this->Verbose)
        {
        cout << "Skipping:" << daA->GetName() << endl;
        }
      return true;
      break;
    }

  if (N<=0)
  {
    return 0;
  }

  if (this->Verbose)
    {
    cout << "Sum(L2)/N of "
         << daA->GetName()
         << " < " << tol
         << "? = " << L2
         << "/" << N
         << "."  << endl;
    }

  double avgL2=L2/static_cast<double>(N);
  if (avgL2>tol)
    {
    return 0;
    }


  return 1;
}
