NzCodeBits(uint32_t nz_coeffs, int nz, int dc_nz) {
  nz_coeffs <<= 2;
  nz_coeffs |= (nz > 3) ? 3 : (nz > 1) ? 2 : dc_nz;
  return nz_coeffs;
}
