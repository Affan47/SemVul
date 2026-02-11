dms2dec (int degrees, int minutes, double seconds, int sw) {
     double st;

     if (degrees < 0)
          degrees = abs(degrees);
     if (minutes < 0)
          minutes = abs(minutes);
     if (seconds < 0)
          seconds = fabs(seconds);

     st = (double)degrees + (double)minutes / 60. + seconds / 3600.;

     if (sw == 1)
          return -st;
     else
          return st;
}
