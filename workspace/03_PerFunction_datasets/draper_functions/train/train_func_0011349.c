Scm_MakeComplexPolar(double mag, double angle)
{
    double real = mag * cos(angle);
    double imag = mag * sin(angle);
    if (imag == 0.0) return Scm_MakeFlonum(real);
    else             return Scm_MakeCompnum(real, imag);
}
