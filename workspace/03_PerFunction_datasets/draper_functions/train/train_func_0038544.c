coordimprov(double *xx, double *yy)
{

  long i, its;

  if (nbody) {


    its = 1;


    for (i=1; i<=its; i++) improvtravn(root);
  } else {
    i = 0;
    do {
      maxchange = 0.0;
      improvtrav(root);
      i++;
    } while ((i < MAXITERATIONS) && (maxchange > MINIMUMCHANGE));
  }
}
