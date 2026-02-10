scm_i_mask32 (scm_t_uint32 m)
{
  return (m < 0x100
	  ? scm_masktab[m]
	  : (m < 0x10000
	     ? scm_masktab[m >> 8] << 8 | 0xff
	     : (m < 0x1000000
		? scm_masktab[m >> 16] << 16 | 0xffff
		: scm_masktab[m >> 24] << 24 | 0xffffff)));
}
