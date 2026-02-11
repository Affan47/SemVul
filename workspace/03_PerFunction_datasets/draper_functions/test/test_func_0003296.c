SetMatrix(int i, vtkMatrix4x4 *matrix)
{
  if (i > 1 || i < 0)
    {
    vtkErrorMacro(<< "Index " << i
      << " is out of range in SetMatrix. Only two matrices allowed!");
    }

  if (matrix == this->Matrix[i])
    {
    return;
    }

  if (this->Transform[i])
    {
    this->Transform[i]->Delete();
    this->Transform[i] = NULL;
    }

  if(this->Matrix[i])
    {
    this->Matrix[i]->Delete();
    this->Matrix[i] = NULL;
    }

  vtkDebugMacro(<< "Setting matrix: " << i << " to point to " << matrix << endl);

  if(matrix)
    {
    this->Matrix[i] = matrix;
    matrix->Register(this);
    vtkMatrixToLinearTransform *transform = vtkMatrixToLinearTransform::New();

    transform->Register(this);
    transform->Delete();
    transform->SetInput(matrix);
    this->Transform[i] = transform;
    vtkDebugMacro(<< "Setting Transform " << i << " to points to: " << transform << endl);
    }
  this->Modified();
}
