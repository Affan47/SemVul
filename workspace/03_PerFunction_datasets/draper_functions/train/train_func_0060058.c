Rotate(Matrix3x3 &M, float theta){
   int row, col;
   Matrix3x3 R(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
   double rad, c, s;

   rad = PI * theta / 180.0;
   c = cos(rad);
   s = sin(rad);

   R[0][0] = c;
   R[0][1] = -s;
   R[1][0] = s;
   R[1][1] = c;

   Matrix3x3 Prod = R * M;

   for(row = 0; row < 3; row++) {
      for(col = 0; col < 3; col++) {
         M[row][col] = Prod[row][col];
      }
   }
}
