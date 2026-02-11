add_dword(dword_t val)
{
  for (int a = 0;a <= 24;a += 8)
    add_char((val >> a) & 0xff);
}
