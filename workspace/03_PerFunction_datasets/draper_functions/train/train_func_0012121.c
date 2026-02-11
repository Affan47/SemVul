matrix_rot_float (float* Y,const float* X,size_t di,size_t dj,size_t n,size_t m)
{
    size_t i,j;
    for (j=0;j<m;j++) {
        size_t j0 = (j+dj)%m;
        for (i=0;i<n;i++) {
            size_t i0 = (i+di)%n;
            Y[i+j*n] = X[i0+j0*n];
        }
    }
}
