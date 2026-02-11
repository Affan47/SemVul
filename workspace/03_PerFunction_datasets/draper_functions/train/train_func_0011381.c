AddIntervalSet(
  double xmin, double xmax, int omin, int omax,
  int assoc, const char* arrayName, int component, int allScalars )
{
  if ( ! arrayName )
    {
    vtkWarningMacro( "You passed a null array name." );
    return -1;
    }

  NormKey nk;

  nk.Association = assoc;
  nk.Type = -1;
  nk.Name = std::string( arrayName );
  nk.Component = component;
  nk.AllScalars = allScalars;

  return this->AddIntervalSet( nk, xmin, xmax, omin, omax );
}
