RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector))
{
  vtkDebugMacro(<<"Executing programmable filter");


  if ( this->ExecuteMethod != NULL )
    {
    (*this->ExecuteMethod)(this->ExecuteMethodArg);
    }

  return 1;
}
