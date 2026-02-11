endian_write_float(void* ptr, float f, int write_le)
{
  char *r = (char *)(void *)&f;
  int i;
  char *optr = (char *) ptr;

  if (i_am_little_endian == write_le) {
    memcpy(ptr, &f, 4);
  } else {
    for (i = 0; i < 4; i++) {
      *optr++ = r[3-i];
    }
  }
}
