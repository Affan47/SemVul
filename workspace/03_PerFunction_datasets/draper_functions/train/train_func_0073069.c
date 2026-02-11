elm_16node_quad_shape_functions()
{
     double u,v;

     int i,j;

     for( i=0; i<16; i++ )
     {
         u = NodeU[i];
         v = NodeV[i];

         A[i][0]  = 1;
         A[i][1]  = u;
         A[i][2]  = u*u;
         A[i][3]  = u*u*u;
         A[i][4]  = v;
         A[i][5]  = u*v;
         A[i][6]  = u*u*v;
         A[i][7]  = u*u*u*v;
         A[i][8]  = v*v;
         A[i][9]  = u*v*v;
         A[i][10] = u*u*v*v;
         A[i][11] = u*u*u*v*v;
         A[i][12] = v*v*v;
         A[i][13] = u*v*v*v;
         A[i][14] = u*u*v*v*v;
         A[i][15] = u*u*u*v*v*v;
     }

     lu_mtrinv( (double *)A,16 );

     for( i=0; i<16; i++ )
        for( j=0; j<16; j++ ) N[i][j] = A[j][i];
}
