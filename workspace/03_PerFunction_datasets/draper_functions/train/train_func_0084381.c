SuiteSparse_divcomplex
(
    double ar, double ai,
    double br, double bi,
    double *cr, double *ci
)
{
    double tr, ti, r, den ;
    if (fabs (br) >= fabs (bi))
    {
	r = bi / br ;
	den = br + r * bi ;
	tr = (ar + ai * r) / den ;
	ti = (ai - ar * r) / den ;
    }
    else
    {
	r = br / bi ;
	den = r * br + bi ;
	tr = (ar * r + ai) / den ;
	ti = (ai * r - ar) / den ;
    }
    *cr = tr ;
    *ci = ti ;
    return (den == 0.) ;
}
