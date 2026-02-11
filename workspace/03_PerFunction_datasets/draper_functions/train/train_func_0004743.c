eraRv2m(double w[3], double r[3][3])


{
   double x, y, z, phi, s, c, f;


   x = w[0];
   y = w[1];
   z = w[2];
   phi = sqrt(x*x + y*y + z*z);
   s = sin(phi);
   c = cos(phi);
   f = 1.0 - c;


   if (phi != 0.0) {
       x /= phi;
       y /= phi;
       z /= phi;
   }


   r[0][0] = x*x*f + c;
   r[0][1] = x*y*f + z*s;
   r[0][2] = x*z*f - y*s;
   r[1][0] = y*x*f - z*s;
   r[1][1] = y*y*f + c;
   r[1][2] = y*z*f + x*s;
   r[2][0] = z*x*f + y*s;
   r[2][1] = z*y*f - x*s;
   r[2][2] = z*z*f + c;

   return;

}
