Plot( double x, double y, int pen )
{


  switch (pen)
  {
    case 3:
    {
      PenUp( x, y );
      break;
    }
    case 2:
    {
      PenDown( x, y );
      break;
    }
    case 20:
    {
      PlotPoint( x, y );
      break;
    }
  }
}
