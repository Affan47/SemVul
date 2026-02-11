xsh_star_flux_list_extrapolate_wave_end( xsh_star_flux_list * list , const double wmax)
{
  XSH_ASSURE_NOT_NULL( list ) ;
  int size=list->size;
  int i=0;
  int k=0;
  int off=10;
  double f1=0;
  double f2=0;
  double w1=0;
  double w2=0;
  double x1=0;
  double x2=0;
  double m=0;
  double x=0;
  double w=0;
  int computed=0;


  for (i = 0; i < size; i++) {
    if (list->lambda[i]<wmax) {
      k++;
    } else {

      if (computed == 0) {
        f2 = list->flux[k];
        f1 = list->flux[k - off];
        w2 = 1./list->lambda[k];
        x2 = w2*w2*w2*w2;
        w1 = 1./list->lambda[k - off];
        x1 = w1*w1*w1*w1;
        m = (f2 - f1) / (x2 - x1);
        computed=1;

      } else {
         w=1./list->lambda[i];
         x=w*w*w*w;

         list->flux[i]=f1+m*(x-x1);

      }
    }
  }

 cleanup:
  return;
}
