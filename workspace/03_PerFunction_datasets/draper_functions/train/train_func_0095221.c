incompleteEllipticEdm(phi,m)
REAL phi,m;
{ if ( m == 0 )
     return -(2*phi-sin(2*phi))/8;
  return (incompleteEllipticE(phi,m)-incompleteEllipticF(phi,m))/2/m;
}
