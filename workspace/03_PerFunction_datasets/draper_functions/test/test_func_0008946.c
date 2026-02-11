write_pixels(FILE *f, int rgb_dir, int vdir, int x, int y, int comp, void *data, int write_alpha, int scanline_pad)
{
   uint8 bg[3] = { 255, 0, 255}, px[3];
   uint32 zero = 0;
   int i,j,k, j_end;

   if (vdir < 0)
      j_end = -1, j = y-1;
   else
      j_end =  y, j = 0;

   for (; j != j_end; j += vdir) {
      for (i=0; i < x; ++i) {
         uint8 *d = (uint8 *) data + (j*x+i)*comp;
         if (write_alpha < 0)
            fwrite(&d[comp-1], 1, 1, f);
         switch (comp) {
            case 1:
            case 2: writef(f, "111", d[0],d[0],d[0]);
                    break;
            case 4:
               if (!write_alpha) {
                  for (k=0; k < 3; ++k)
                     px[k] = bg[k] + ((d[k] - bg[k]) * d[3])/255;
                  writef(f, "111", px[1-rgb_dir],px[1],px[1+rgb_dir]);
                  break;
               }

            case 3:
               writef(f, "111", d[1-rgb_dir],d[1],d[1+rgb_dir]);
               break;
         }
         if (write_alpha > 0)
            fwrite(&d[comp-1], 1, 1, f);
      }
      fwrite(&zero,scanline_pad,1,f);
   }
}
