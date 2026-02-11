RequestInformation (
  vtkInformation * vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);


  int     numTimes = 0;
  double *inTimes  = NULL;
  double  outRange[2];

  if (inInfo->Has(vtkStreamingDemandDrivenPipeline::TIME_STEPS()))
    {
    inTimes =
      inInfo->Get(vtkStreamingDemandDrivenPipeline::TIME_STEPS());
    numTimes =
      inInfo->Length(vtkStreamingDemandDrivenPipeline::TIME_STEPS());

    outRange[0] = inTimes[0];
    outRange[1] = inTimes[numTimes-1];
    outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(),
                 outRange,2);
    }


  if (numTimes<2)
    {
    vtkErrorMacro(<<"Not enough input time steps for interpolation");
    return 0;
    }


  if (this->DiscreteTimeStepInterval>0.0)
    {


    int NumberOfOutputTimeSteps = 1 +
      static_cast<int>(0.5+((outRange[1]-outRange[0])/this->DiscreteTimeStepInterval));


    std::vector<double> OutputTimeValues;
    for (int i=0; i<NumberOfOutputTimeSteps; i++)
      {
      OutputTimeValues.push_back(
        (double)(i)*this->DiscreteTimeStepInterval + outRange[0]);
      }
    outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(),
      &OutputTimeValues[0], NumberOfOutputTimeSteps);
    }
  else if (this->ResampleFactor>0)
    {

    std::vector<double> OutputTimeValues;
    OutputTimeValues.reserve(numTimes*this->ResampleFactor);
    for (int i=1; i<numTimes; i++)
      {
      double t0 = inTimes[i-1];
      double t1 = inTimes[i];
      double step = (t1-t0)/(double)this->ResampleFactor;
      for (int j=0; j<this->ResampleFactor; j++)
        {
        double newT = t0 + j*step;
        OutputTimeValues.push_back(newT);
        }
      }
    outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(),
      &OutputTimeValues[0], static_cast<int>(OutputTimeValues.size()));
    }
  else
    {

    if (outInfo->Has(vtkStreamingDemandDrivenPipeline::TIME_STEPS()))
      {
      outInfo->Remove(vtkStreamingDemandDrivenPipeline::TIME_STEPS());
      }
    }
  return 1;
}
