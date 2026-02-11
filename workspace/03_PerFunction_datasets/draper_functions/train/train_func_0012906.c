ContinueLine( double x, double y )
{


  static int op = 0;
  static double xOld = 0.0;
  static double yOld = 0.0;
  static double distanceTraveled = 0.0;

  if( x==xPrevious_ && y==yPrevious_ )return;


  double p1 = drawLineTable_[0][lineType_-1];
  double p2 = drawLineTable_[1][lineType_-1];
  double p3 = drawLineTable_[2][lineType_-1];

  if( p1 == 0. )
  {
    PenDown( x, y );
  }
  else
  {
    double const deltx = x-xPrevious_;
    double const delty = y-yPrevious_;
    double const distanceToTravel = sqrt(deltx*deltx + delty*delty);

    double sinth = delty/distanceToTravel;
    double costh = deltx/distanceToTravel;

    if( p2 == 0. )
    {
      double hwid = p1/2.0;
      double dx = hwid*sinth;
      double dy = hwid*costh;
      double xloc = xPrevious_;
      double yloc = yPrevious_;
      PenUp( xloc-dx, yloc+dy );
      PenDown( x-dx, y+dy );
      PenUp( xloc+dx, yloc-dy );
      PenDown( x+dx, y-dy );
    }
    else
    {
      if( p3 == 0. )p3 = p1;

      double dd[4];
      dd[0] = p1;
      dd[1] = p2;
      dd[2] = p3;
      dd[3] = p2;

      double const x0 = xPrevious_;
      double const y0 = yPrevious_;


      double const eps = 0.0001;
      if( !newLine_ && fabs(x0-xOld)<eps && fabs(y0-yOld)<eps )
      {
        if( distanceTraveled > 0. )goto L210;
        goto L200;
      }


      op = 0;
      distanceTraveled = 0.0;
 L200:
      if( ++op == 5 )op = 1;
      distanceTraveled += dd[op-1];
      L210:
      double xloc = x0 + distanceTraveled*costh;
      double yloc = y0 + distanceTraveled*sinth;
      bool drawTo = (op==1||op==3);


      if( distanceTraveled >= distanceToTravel )
      {
        xloc = x;
        yloc = y;

      }
      drawTo ? PenDown(xloc,yloc) : PenUp(xloc,yloc);
      if( distanceTraveled < distanceToTravel )goto L200;
    }
    xOld = x;
    yOld = y;
    distanceTraveled -= distanceToTravel;
  }
  newLine_ = false;
}
