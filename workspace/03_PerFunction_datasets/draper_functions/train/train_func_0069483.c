matmul34( GLfloat *product, const GLfloat *a, const GLfloat *b )
{
   GLint i;
   for (i = 0; i < 3; i++) {
      const GLfloat ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3;
   }
   P(3,0) = 0;
   P(3,1) = 0;
   P(3,2) = 0;
   P(3,3) = 1;
}
