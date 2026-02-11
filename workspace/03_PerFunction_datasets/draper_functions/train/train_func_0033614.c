subcurve(double *pole, int pole_step, double t0, double t1)
{

    double q0 = pole[pole_step * 0];
    double q1 = pole[pole_step * 1];
    double q2 = pole[pole_step * 2];
    double q3 = pole[pole_step * 3];
    double t01 = t0 - 1, t11 = t1 - 1;
    double small = 1e-13;

#define Power2(a) (a) * (a)
#define Power3(a) (a) * (a) * (a)
    pole[pole_step * 0] = t0*(t0*(q3*t0 - 3*q2*t01) + 3*q1*Power2(t01)) - q0*Power3(t01);
    pole[pole_step * 1] = q1*t01*(-2*t0 - t1 + 3*t0*t1) + t0*(q2*t0 + 2*q2*t1 -
                            3*q2*t0*t1 + q3*t0*t1) - q0*t11*Power2(t01);
    pole[pole_step * 2] = t1*(2*q2*t0 + q2*t1 - 3*q2*t0*t1 + q3*t0*t1) +
                            q1*(-t0 - 2*t1 + 3*t0*t1)*t11 - q0*t01*Power2(t11);
    pole[pole_step * 3] = t1*(t1*(3*q2 - 3*q2*t1 + q3*t1) +
                            3*q1*Power2(t11)) - q0*Power3(t11);
#undef Power2
#undef Power3
    if (any_abs(pole[pole_step * 1] - pole[pole_step * 0]) < small)
        pole[pole_step * 1] = pole[pole_step * 0];
    if (any_abs(pole[pole_step * 2] - pole[pole_step * 3]) < small)
        pole[pole_step * 2] = pole[pole_step * 3];
}
