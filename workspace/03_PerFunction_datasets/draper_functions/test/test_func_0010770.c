arcfour_encrypt(struct arcfour_key * key,
                     char * src, char * dst, long len)
{
  int x, y, kx, ky;

  x = key->x;
  y = key->y;
  for (; len > 0; len--) {
    x = (x + 1) & 0xFF;
    kx = key->state[x];
    y = (kx + y) & 0xFF;
    ky = key->state[y];
    key->state[x] = ky; key->state[y] = kx;
    *dst++ = *src++ ^ key->state[(kx + ky) & 0xFF];
  }
  key->x = x;
  key->y = y;
}
