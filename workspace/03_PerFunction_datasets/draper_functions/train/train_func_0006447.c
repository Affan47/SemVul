ellipticKdmdm(m)
REAL m;
{ return (m == 0) ? 9./64*M_PI :
     ((4*m-2)*ellipticE(m) + (2-5*m+3*m*m)*ellipticK(m))/4/m/m/(1-m)/(1-m);
}
