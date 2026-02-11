flam3_create_xform_distrib(flam3_genome *cp) {


   int numrows;
   int dist_row,i;
   unsigned short *xform_distrib;

   numrows = cp->num_xforms - (cp->final_xform_index>=0) + 1;
   xform_distrib = calloc(numrows*CHOOSE_XFORM_GRAIN,sizeof(unsigned short));


   flam3_create_chaos_distrib(cp, -1, xform_distrib);


   cp->chaos_enable = 1 - flam3_check_unity_chaos(cp);

   if (cp->chaos_enable) {


      dist_row = 0;
      for (i=0;i<cp->num_xforms;i++) {

         if (cp->final_xform_index == i)
            continue;
         else
            dist_row++;

         if (flam3_create_chaos_distrib(cp, i, &(xform_distrib[CHOOSE_XFORM_GRAIN*(dist_row)]))) {
            free(xform_distrib);
            return(NULL);
         }
      }
   }

   return(xform_distrib);
}
