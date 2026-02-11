T1_DoLine ( long wd, long paddedW, char *ptr, register char *target_ptr )
{
  register int j;
  register unsigned char *in_ptr;
  T1_AA_TYPE16 *starget_ptr;
  T1_AA_TYPE32 *ltarget_ptr;

  in_ptr=(unsigned char *)ptr;

  if (T1aa_bpp==8) {
    for ( j=0; j<wd; j++ ){
      *target_ptr++=T1aa_n_lut[((in_ptr[j/8])>>j%8)&0x0F];
    }
  }
  else if (T1aa_bpp==16) {
    starget_ptr=(T1_AA_TYPE16 *)target_ptr;
    for ( j=0; j<wd; j++){
      *starget_ptr++=T1aa_n_lut[((in_ptr[j/8])>>j%8)&0x03];
    }
  }
  else if (T1aa_bpp==32) {
    ltarget_ptr=(T1_AA_TYPE32 *)target_ptr;
    for ( j=0; j<wd; j++)
      *ltarget_ptr++=T1aa_n_lut[((in_ptr[j/8])>>j%8)&0x01];
  }
  return;
}
