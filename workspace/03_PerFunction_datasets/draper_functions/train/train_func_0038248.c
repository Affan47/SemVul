flam3_improve_colors(flam3_genome *g, int ntries, int change_palette, int color_resolution) {
   int i;
   double best, b;
   flam3_genome best_genome;

   memset(&best_genome, 0, sizeof(flam3_genome));

   best = try_colors(g, color_resolution);
   if (best<0) {
      fprintf(stderr,"error in try_colors, skipping flam3_improve_colors\n");
      return;
   }

   flam3_copy(&best_genome,g);
   for (i = 0; i < ntries; i++) {
      change_colors(g, change_palette);
      b = try_colors(g, color_resolution);
      if (b < 0) {
         fprintf(stderr,"error in try_colors, aborting tries\n");
         break;
      }
      if (b > best) {
         best = b;
         flam3_copy(&best_genome,g);
      }
   }

   flam3_copy(g,&best_genome);
   clear_cp(&best_genome,flam3_defaults_on);
}
