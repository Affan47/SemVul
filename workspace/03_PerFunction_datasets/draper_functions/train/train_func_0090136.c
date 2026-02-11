PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  if ( this->Input )
    {
    os << indent << "Input: (" << this->Input << ")\n";
    }
  else
    {
    os << indent << "Input: (none)\n";
    }

  if ( this->DirectionEncoder )
    {
    os << indent << "DirectionEncoder: (" << this->DirectionEncoder << ")\n";
    }
  else
    {
    os << indent << "DirectionEncoder: (none)\n";
    }

  os << indent << "Build Time: "
     << this->BuildTime.GetMTime() << endl;

  os << indent << "Gradient Magnitude Scale: "
     << this->GradientMagnitudeScale << endl;

  os << indent << "Gradient Magnitude Bias: "
     << this->GradientMagnitudeBias << endl;

  os << indent << "Zero Pad: "
     << ((this->ZeroPad)?"On":"Off") << endl;

  os << indent << "Bounds Clip: "
     << ((this->BoundsClip)?"On":"Off") << endl;

  os << indent << "Bounds: ("
     << this->Bounds[0] << ", " << this->Bounds[1] << ", "
     << this->Bounds[2] << ", " << this->Bounds[3] << ", "
     << this->Bounds[4] << ", " << this->Bounds[5] << ")\n";

  os << indent << "Zero Normal Threshold: "
     << this->ZeroNormalThreshold << endl;

  os << indent << "Compute Gradient Magnitudes: "
     << ((this->ComputeGradientMagnitudes)?"On":"Off") << endl;

  os << indent << "Cylinder Clip: "
     << ((this->CylinderClip)?"On":"Off") << endl;

  os << indent << "Number Of Threads: "
     << this->NumberOfThreads << endl;

  os << indent << "Last Update Time In Seconds: "
     << this->LastUpdateTimeInSeconds << endl;

  os << indent << "Last Update Time In CPU Seconds: "
     << this->LastUpdateTimeInCPUSeconds << endl;


}
