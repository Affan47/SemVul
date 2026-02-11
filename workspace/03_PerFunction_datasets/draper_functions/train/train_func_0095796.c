vector_rand_float (float* v,float fMin,float fMax,size_t n)
{
    size_t i;
    double r;
    for (i=0;i<n;i++) {
        r = rand()%1000000000;
        r /= 1000000000;
        v[i] = fMin + r * (fMax - fMin);
    }
}
