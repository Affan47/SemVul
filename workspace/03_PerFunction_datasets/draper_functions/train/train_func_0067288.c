ComputeTemperature(vtkStructuredGrid* output)
{
  double *m, e, rr, u, v, w, v2, p, d, rrgas;
  vtkIdType i;
  vtkFloatArray *temperature;


  vtkPointData* outputPD = output->GetPointData();
  vtkDataArray* density = outputPD->GetArray("Density");
  vtkDataArray* momentum = outputPD->GetArray("Momentum");
  vtkDataArray* energy = outputPD->GetArray("StagnationEnergy");

  if ( density == NULL || momentum == NULL ||
       energy == NULL )
    {
    vtkErrorMacro(<<"Cannot compute temperature");
    return;
    }

  vtkIdType numPts = density->GetNumberOfTuples();
  temperature = vtkFloatArray::New();
  temperature->SetNumberOfTuples(numPts);


  rrgas = 1.0 / this->R;
  for (i=0; i < numPts; i++)
    {
    d = density->GetComponent(i,0);
    d = (d != 0.0 ? d : 1.0);
    m = momentum->GetTuple(i);
    e = energy->GetComponent(i,0);
    rr = 1.0 / d;
    u = m[0] * rr;
    v = m[1] * rr;
    w = m[2] * rr;
    v2 = u*u + v*v + w*w;
    p = (this->Gamma-1.) * (e - 0.5 * d * v2);
    temperature->SetValue(i, p*rr*rrgas);
  }

  temperature->SetName("Temperature");
  outputPD->AddArray(temperature);

  temperature->Delete();
  vtkDebugMacro(<<"Created temperature scalar");
}
