v_hex_get_weight( VerdictVector &v1,
    VerdictVector &v2,
    VerdictVector &v3 )
{

  if ( v_hex_size == 0)
    return 0;

  v1.set(1,0,0);
  v2.set(0,1,0);
  v3.set(0,0,1);

  double scale = pow(v_hex_size/ (v1 % (v2 * v3 )), 0.33333333333);
  v1 *= scale;
  v2 *= scale;
  v3 *= scale;

  return 1;
}
