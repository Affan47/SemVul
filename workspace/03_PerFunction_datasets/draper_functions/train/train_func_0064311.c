h_dnnt(doublereal *x)
#endif
{
return (shortint)(*x >= 0. ? floor(*x + .5) : -floor(.5 - *x));
}
