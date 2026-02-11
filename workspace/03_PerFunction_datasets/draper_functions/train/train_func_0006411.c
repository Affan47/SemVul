teepee (const gfloat c_major_x,
        const gfloat c_major_y,
        const gfloat c_minor_x,
        const gfloat c_minor_y,
        const gfloat s,
        const gfloat t)
{
  const gfloat q1 = s * c_major_x + t * c_major_y;
  const gfloat q2 = s * c_minor_x + t * c_minor_y;
  const gfloat r2 = q1 * q1 + q2 * q2;
  const gfloat weight =
    r2 < (gfloat) 1.
    ?
    (gfloat) ( (gfloat) 1. - sqrtf( (float) r2 ) )
    :
    (gfloat) 0.;

  return weight;
}
