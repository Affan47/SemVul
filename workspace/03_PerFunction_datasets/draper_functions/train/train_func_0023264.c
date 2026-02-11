GetNodeGeometry( double center[3], double& sz )
{
  const double* x = this->Node->value().GetCenter();
  for ( int i = 0; i < 2; ++ i )
    center[i] = x[i];
  center[2] = this->Hierarchy->GetImplementation()->Z2;
  sz = this->Node->value().GetSize() / 2.;
}
