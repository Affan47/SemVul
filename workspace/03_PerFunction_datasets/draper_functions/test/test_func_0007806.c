is_real(double x)
{
    const double Inf = 1.0 / 0.0;
    return (x < Inf) && (x >= -Inf);
}
