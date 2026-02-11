difference_of_angles(double a1, double a2)
{
    double d = a1 - a2;

    while (d < -CPL_MATH_PI) d += CPL_MATH_2PI;
    while (d >  CPL_MATH_PI) d -= CPL_MATH_2PI;

    return fabs(d);
}
