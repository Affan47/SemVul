elm_5node_quad_shape_functions()
{
     double u,v;

     int i,j;

     for( i=0; i<5; i++ )
     {
         u = NodeU[i];
         v = NodeV[i];

         A[i][0]  = 1;
         A[i][1]  = u;
         A[i][2]  = v;
         A[i][3]  = u*v;
         A[i][4]  = u*u*v*v;
     }

     lu_mtrinv( (double *)A,5 );

     for( i=0; i<5; i++ )
        for( j=0; j<5; j++ ) N[i][j] = A[j][i];
}
