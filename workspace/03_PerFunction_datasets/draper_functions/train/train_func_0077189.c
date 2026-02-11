set_parameter(int param, CHAIN_OPERATOR::parameter_t value)
{
  switch (param) {
  case 1:
    center = value;
    D = 2 * cos(2 * M_PI * center / (CHAIN_OPERATOR::parameter_t)samples_per_second());
    b[0] = -C * D * a[0];
    break;
  case 2:
    if (value != 0) width = value;
    else width = center / 2;
    C = 1.0 / tan(M_PI * width / (CHAIN_OPERATOR::parameter_t)samples_per_second());
    D = 2 * cos(2 * M_PI * center / (CHAIN_OPERATOR::parameter_t)samples_per_second());
    a[0] = 1.0 / (1.0 + C);
    a[1] = 0.0;
    a[2] = -a[0];
    b[0] = -C * D * a[0];
    b[1] = (C - 1.0) * a[0];
    break;
  }
}
