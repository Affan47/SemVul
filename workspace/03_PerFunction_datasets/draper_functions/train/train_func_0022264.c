float2long( v )
float		v;
{
  long  i;
  float	r;

  i = v;
  r = v-i;

  if( r >= 0.5 )
    return ( i+1 );
  return(i);
}
