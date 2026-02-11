LynxSaveFigure( Figure, Real )

  void *Figure;
  char  Real;
{
  if ( Real )
  {
    saverdsfig( Figure );
  }
  else
  {
    savephfig( Figure );
  }
}
