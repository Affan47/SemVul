setup_circle (gleGC *gc, int nslices)
{
   int i;
   double c, s;

   if (!gc) return;
   if (0 > nslices) return;
   if (nslices == gc->slices) return;

   if (nslices > gc->slices) {
      gc->circle = (gleTwoVec *) realloc (gc->circle,
                                          sizeof(gleTwoVec)*2*nslices);
      gc->norm = &(gc->circle)[nslices];
   }

   s = sin (2.0*M_PI/ ((double) nslices));
   c = cos (2.0*M_PI/ ((double) nslices));

   gc->norm [0][0] = 1.0;
   gc->norm [0][1] = 0.0;


   for (i=1; i<nslices; i++) {
      gc->norm [i][0] = gc->norm[i-1][0] * c - gc->norm[i-1][1] * s;
      gc->norm [i][1] = gc->norm[i-1][0] * s + gc->norm[i-1][1] * c;
   }

  gc->slices = nslices;
}
