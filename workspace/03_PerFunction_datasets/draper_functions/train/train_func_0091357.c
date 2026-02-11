validate_mode (struct mode_data *m,
	       enum requirement r_precision,
	       enum requirement r_bytesize,
	       enum requirement r_component,
	       enum requirement r_ncomponents,
	       enum requirement r_format)
{
  validate_field (m, precision);
  validate_field (m, bytesize);
  validate_field (m, component);
  validate_field (m, ncomponents);
  validate_field (m, format);
}
