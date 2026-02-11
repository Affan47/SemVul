dirbinarize(const unsigned char *pptr, const int idir,
                const ROTGRIDS *dirbingrids)
{
   int gx, gy, gi, cy;
   int rsum, gsum, csum = 0;
   int *grid;
   double dcy;


   grid = dirbingrids->grids[idir];

   dcy = (dirbingrids->grid_h-1)/(double)2.0;


   dcy = trunc_dbl_precision(dcy, TRUNC_SCALE);
   cy = sround(dcy);

   gi = 0;

   gsum = 0;


   for(gy = 0; gy < dirbingrids->grid_h; gy++){

      rsum = 0;

      for(gx = 0; gx < dirbingrids->grid_w; gx++){

         rsum += *(pptr+grid[gi]);

         gi++;
      }

      gsum += rsum;

      if(gy == cy)
         csum = rsum;
   }


   if((csum * dirbingrids->grid_h) < gsum)

      return(BLACK_PIXEL);
   else

      return(WHITE_PIXEL);
}
