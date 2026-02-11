PSF_G(double  f,
                    double  u)
{
    if (f <= (1.0-u)/2.0) return(u*u);
    if (f >= (1.0+u)/2.0) return(0.0);
    else return(PSF_H1(f,u,1.0) + PSF_H1(f,u,u) + PSF_H2(f,u));
}
