SetWindowLevel(double window, double level, int copy)
{
  if ( copy )
    {
    this->CurrentWindow = window;
    this->CurrentLevel = level;
    return;
    }

  if ( this->CurrentWindow == window && this->CurrentLevel == level )
    {
    return;
    }


  if ( (( window < 0 && this->CurrentWindow > 0 ) ||
        ( window > 0 && this->CurrentWindow < 0 )) &&
        !this->UserControlledLookupTable )
    {
    this->InvertTable();
    }

  this->CurrentWindow = window;
  this->CurrentLevel = level;

  if ( !this->UserControlledLookupTable )
    {
    double rmin = this->CurrentLevel - 0.5*fabs( this->CurrentWindow );
    double rmax = rmin + fabs( this->CurrentWindow );
    this->LookupTable->SetTableRange( rmin, rmax );
    }

  if ( this->Enabled )
    {
    this->Interactor->Render();
    }
}
