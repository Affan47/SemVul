immnum_signum(object x) {
  ufixnum ux=(ufixnum)x,uz=((ufixnum)({register fixnum _q1=(0);register object _q4; _q4=(!(((_q1)+(0x4000000000000000>>1))&-0x4000000000000000)) ? ((object)((_q1)+(0x8000000000000000 +(0x4000000000000000>>1)))) : make_fixnum1(_q1);_q4;}));
  return (((ufixnum)(x))>=0x8000000000000000) ? (ux<uz ? ((object)((-1)+(0x8000000000000000 +(0x4000000000000000>>1)))) : (ux==uz ? ((object)((0)+(0x8000000000000000 +(0x4000000000000000>>1)))) : ((object)((1)+(0x8000000000000000 +(0x4000000000000000>>1)))))) : number_signum(x);
}
