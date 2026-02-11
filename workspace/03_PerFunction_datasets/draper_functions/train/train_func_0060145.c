xThetaYRToScreen(CoordSettings coord, double xTheta, double yR,
  double* xScreen, double* yScreen) const
{
  if (validAxes() || validScale())
  {
    linearToLog(coord, &xTheta, &yR);

    double xGraph, yGraph;
    converttocartesian(mmUnitize(coord), xTheta, yR, coord.originRadius, &xGraph, &yGraph);

    graphToScreen(xGraph, yGraph, xScreen, yScreen);
  }
  else
  {


    *xScreen = xTheta;
    *yScreen = yR;
  }
}
