jitter_randval (gint type)
{


  gdouble drand;
  static gdouble dsave;
  static gboolean isave = false;

  if (type == UNIFORM) {
    drand = randvalue ();


    drand = (drand - .5) * 2;

  }
  else if (type == NORMAL) {

    gboolean check = true;
    gdouble d, dfac;

    if (isave) {
      isave = false;

      drand = dsave;
    }
    else {
      isave = true;
      while (check) {

        rnorm2 (&drand, &dsave);
        d = drand * drand + dsave * dsave;

        if (d < 1.0) {
          check = false;
          dfac = sqrt (-2. * log (d) / d);
          drand = drand * dfac;
          dsave = dsave * dfac;
        }
      }
    }


    drand = (drand / 3.0);
  }
  return ((gfloat) drand);
}
