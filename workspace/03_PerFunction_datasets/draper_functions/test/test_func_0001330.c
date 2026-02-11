d_sign(double *arg1, double *arg2){
   if (*arg2>=0.0) return dblabs(*arg1);
   else return -1.0*dblabs(*arg1);
}
