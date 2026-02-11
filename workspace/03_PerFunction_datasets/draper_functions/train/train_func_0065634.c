_tenAnisoTen_Q_f(const float  ten[7]) {
  float A, B;
  A = -TEN_T_TRACE(ten);
  B = _tenAnisoTen_B_f(ten);
  A = (A*A - 3.0f*B)/9.0f;
  return AIR_MAX(0, A);
}
