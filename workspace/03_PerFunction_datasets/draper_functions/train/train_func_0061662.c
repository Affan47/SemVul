ipmi_sensor_decode_resolution (int8_t r_exponent,
                               int16_t m,
                               double *value)
{
  double dval = 0.0;

  if (!value)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  dval = abs (m * pow (10, r_exponent));

  *value = dval;
  return (0);
}
