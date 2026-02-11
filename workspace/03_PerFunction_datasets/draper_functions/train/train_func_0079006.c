log_multigamma(double n, unsigned int p)
{
    double y =  (p * (p-1) * log(M_PI))/4;
    for (unsigned int j = 0; j < p; ++j) {
        y += lgammafn((n-j)/2);
    }
    return y;
}
