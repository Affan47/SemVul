main()
{
  const std::complex<double> neg1(-1.0, 0.0);
  const std::complex<double> half(0.5,0.0);
  const std::complex<double> i(0.0, 1.0);
  std::complex<double> sqrt_neg1 = std::pow(neg1, 0.5);
  double error = std::abs(sqrt_neg1-i);


  if ( error >= 0 && -error > -1e-6)
  {}
  else
    return 1;
  if (error != error)
    return 1;

  sqrt_neg1 = std::pow(neg1, half);
  error = std::abs(sqrt_neg1-i);
  if ( error >= 0 && -error > -1e-6)
  {}
  else
    return 1;
  if (error != error)
    return 1;

  sqrt_neg1 = std::pow(-1.0, half);
  error = std::abs(sqrt_neg1-i);
  if ( error >= 0 && -error > -1e-6)
  {}
  else
    return 1;
  if (error != error)
    return 1;

  return 0;
}
