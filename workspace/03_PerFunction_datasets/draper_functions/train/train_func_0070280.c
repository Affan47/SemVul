flam3_rotate(flam3_genome *cp, double by, int interpolation_type) {
   int i;
   for (i = 0; i < cp->num_xforms; i++) {
      double r[2][2];
      double T[2][2];
      double U[2][2];
      double dtheta = by * 2.0 * M_PI / 360.0;


      if (cp->xform[i].animate == 0.0)
         continue;

      if (cp->xform[i].padding == 1) {
         if (interpolation_type == flam3_inttype_compat) {

            continue;
         } else if (interpolation_type == flam3_inttype_older) {

            continue;
         } else if (interpolation_type == flam3_inttype_linear) {

            continue;
         } else if (interpolation_type == flam3_inttype_log) {


         }
      }


      if (cp->final_xform_enable==1 && cp->final_xform_index==i)
         continue;

      r[1][1] = r[0][0] = cos(dtheta);
      r[0][1] = sin(dtheta);
      r[1][0] = -r[0][1];
      T[0][0] = cp->xform[i].c[0][0];
      T[1][0] = cp->xform[i].c[1][0];
      T[0][1] = cp->xform[i].c[0][1];
      T[1][1] = cp->xform[i].c[1][1];
      mult_matrix(r, T, U);
      cp->xform[i].c[0][0] = U[0][0];
      cp->xform[i].c[1][0] = U[1][0];
      cp->xform[i].c[0][1] = U[0][1];
      cp->xform[i].c[1][1] = U[1][1];
   }
}
