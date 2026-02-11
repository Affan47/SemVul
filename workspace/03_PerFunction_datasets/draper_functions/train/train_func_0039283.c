ffh(F *xp,I n) {
  union {
    int z[2];
    F f;
  } u;

  while(--n&&!*xp) {
    ++xp;
  }
  u.f=*xp;
  R(u.z[1]&0x7FFFFFFF)^(u.z[0]&0xFFFFF000);
}
