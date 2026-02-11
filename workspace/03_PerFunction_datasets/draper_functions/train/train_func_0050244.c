PackFloatArray()
{


  vtkIdType len = 4 +
                  this->SizeBlockAttributeArray +
                  this->SumDistFactPerNodeSet +
                  this->SumDistFactPerSideSet +
                  this->NumberOfGlobalVariables +
                  this->NumberOfTimeSteps;

  float *f = new float [len];

  f[0] = static_cast<float>(this->SizeBlockAttributeArray);
  f[1] = static_cast<float>(this->SumDistFactPerNodeSet);
  f[2] = static_cast<float>(this->SumDistFactPerSideSet);
  f[3] = static_cast<float>(this->NumberOfTimeSteps);

  float *nextf = f + 4;

  if (this->SizeBlockAttributeArray)
    {
    memcpy(nextf, this->BlockAttributes,
              this->SizeBlockAttributeArray * sizeof(float));
    nextf += this->SizeBlockAttributeArray;
    }

  if (this->SumDistFactPerNodeSet)
    {
    memcpy(nextf, this->NodeSetDistributionFactors,
              this->SumDistFactPerNodeSet * sizeof(float));
    nextf += this->SumDistFactPerNodeSet;
    }

  if (this->SumDistFactPerSideSet)
    {
    memcpy(nextf, this->SideSetDistributionFactors,
              this->SumDistFactPerSideSet * sizeof(float));
    nextf += this->SumDistFactPerSideSet;
    }

  if (this->NumberOfGlobalVariables)
    {
    memcpy(nextf, this->GlobalVariableValue,
              this->NumberOfGlobalVariables * sizeof(float));
    nextf += this->NumberOfGlobalVariables;
    }

  if (this->NumberOfTimeSteps)
    {
    memcpy(nextf, this->TimeStepValues,
              this->NumberOfTimeSteps* sizeof(float));
    nextf += this->NumberOfTimeSteps;
    }

  vtkFloatArray *fa = vtkFloatArray::New();
  fa->SetArray(f, len, 0);
  fa->SetName(FLOAT_ARRAY);

  return fa;
}
