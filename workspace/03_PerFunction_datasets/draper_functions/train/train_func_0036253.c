azprev(x, y, prj, phi, theta)

const double x, y;
struct prjprm *prj;
double *phi, *theta;

{
   double r, rho, s;
   const double tol = 1.0e-13;

   if (abs(prj->flag) != PRJSET) {
      if (vimosazpset(prj)) return 1;
   }

   r = sqrt(x*x + y*y);
   if (r == 0.0) {
      *phi = 0.0;
   } else {
      *phi = atan2deg (x, -y);
   }

   rho = r*prj->w[1];
   s = rho*prj->p[1]/sqrt(rho*rho+1.0);
   if (fabs(s) > 1.0) {
      if (fabs(s) > 1.0+tol) {
         return 2;
      }
      *theta = atan2deg (1.0,rho) - copysign(90.0,s);
   } else {
      *theta = atan2deg (1.0,rho) - asindeg (s);
   }

   return 0;
}
