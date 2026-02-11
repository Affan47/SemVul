c_plsurf3d(PLFLT *x, PLFLT *y, PLFLT **z, PLINT nx, PLINT ny,
	  PLINT opt, PLFLT *clevel, PLINT nlevel)
{
   PLINT i;
   PLINT *indexymin = (PLINT *) malloc((size_t) (nx*sizeof(PLINT)));
   PLINT *indexymax = (PLINT *) malloc((size_t) (nx*sizeof(PLINT)));

   if ( ! indexymin || ! indexymax)
     plexit("plsurf3d: Out of memory.");
   for (i = 0; i < nx; i++) {
      indexymin[i] = 0;
      indexymax[i] = ny;
   }
   c_plsurf3dl(x, y, z, nx, ny, opt, clevel, nlevel,
	       0, nx, indexymin, indexymax);
   free_mem(indexymin);
   free_mem(indexymax);
}
