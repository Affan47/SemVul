_mesa_noise1(GLfloat x)
{
   int i0 = FASTFLOOR(x);
   int i1 = i0 + 1;
   float x0 = x - i0;
   float x1 = x0 - 1.0f;
   float t1 = 1.0f - x1 * x1;
   float n0, n1;

   float t0 = 1.0f - x0 * x0;

   t0 *= t0;
   n0 = t0 * t0 * grad1(perm[i0 & 0xff], x0);


   t1 *= t1;
   n1 = t1 * t1 * grad1(perm[i1 & 0xff], x1);


   return 0.25f * (n0 + n1);
}
