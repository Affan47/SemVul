cvec_dot_prodi32(const complexi32_t x[], const complexi32_t y[], int n)
{
    int i;
    complexi32_t z;

    z = complex_seti32(0, 0);
    for (i = 0;  i < n;  i++)
    {
        z.re += (x[i].re*y[i].re - x[i].im*y[i].im);
        z.im += (x[i].re*y[i].im + x[i].im*y[i].re);
    }
    return z;
}
