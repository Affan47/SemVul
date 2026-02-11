intpoly6part(k,i,u,v)
int k;
int i;
REAL u,v;
{
  if ( i == 0 )
    switch ( k )
     {
        case 0: return u + v - 1.5;
        case 1: return 2 - 2*u - v;
        case 2: return u - 0.5;
        case 3: return v;
        case 4: return 0.0;
        case 5: return -v;
     }
  else if ( i == 1 )
    switch ( k )
     {
        case 0: return u + v - 1.5;
        case 1: return -u;
        case 2: return 0.0;
        case 3: return u;
        case 4: return v - 0.5;
        case 5: return 2 - u - 2*v;
     }


  return 0.0;
}
