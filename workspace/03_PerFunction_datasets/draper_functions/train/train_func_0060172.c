var74_split (flam3_iter_helper *f, double weight) {


   if (cos(f->tx*f->xform->split_xsize*M_PI) >= 0)
      f->p1 += weight*f->ty;
   else
      f->p1 -= weight*f->ty;

   if (cos(f->ty*f->xform->split_ysize*M_PI) >= 0)
      f->p0 += weight * f->tx;
   else
      f->p0 -= weight * f->tx;

}
