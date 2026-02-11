des_lpba(double rate, double f0, double f1, int order, int n_arg, double *arg) {
   double wid= 0.3189435/f0;
   double tot, adj;
   int max= (int)floor(wid);
   int a;
   FidFilter *ff= Alloc(FFCSIZE(1, max*2+1));
   ff->typ= 'F';
   ff->cbm= 0;
   ff->len= max*2+1;
   ff->val[max]= tot= 1.0;
   for (a= 1; a<=max; a++) {
      double val= 1.0 - a/wid;
      ff->val[max-a]= val;
      ff->val[max+a]= val;
      tot += val * 2.0;
   }
   adj= 1/tot;
   for (a= 0; a<=max*2; a++) ff->val[a] *= adj;
   return ff;
}
