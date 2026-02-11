var33_juliaScope_generic (flam3_iter_helper *f, double weight) {


   int t_rnd = trunc((f->xform->juliascope_rN) * flam3_random_isaac_01(f->rc));

   double tmpr, r;
   double sina, cosa;

   if ((t_rnd & 1) == 0)
      tmpr = (2 * M_PI * t_rnd + f->precalc_atanyx) / f->xform->juliascope_power;
   else
      tmpr = (2 * M_PI * t_rnd - f->precalc_atanyx) / f->xform->juliascope_power;

   sincos(tmpr,&sina,&cosa);

   r = weight * pow(f->precalc_sumsq, f->xform->juliascope_cn);

   f->p0 += r * cosa;
   f->p1 += r * sina;
}
