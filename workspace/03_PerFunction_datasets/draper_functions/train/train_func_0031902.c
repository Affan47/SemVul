polar2xy(double phi, double rho, double *x, double *y)
{
    if (rho < 0.0) {
        return (RETURN_FAILURE);
    } else {
        *x = rho*cos(phi);
        *y = rho*sin(phi);
        return (RETURN_SUCCESS);
    }
}
