list_add_wrapper (listz_t p, listz_t q, listz_t r, unsigned int n,
                  unsigned int max_r)
{
    list_add (p, q, r, MIN (n, max_r));
    if (n > max_r)
      list_set (p + max_r, q + max_r, n - max_r);
}
