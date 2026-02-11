agt_rand (int a, int b)
{
  static int is_initialized = FALSE;

  int result;

  if (!is_initialized)
    {
      srand (stable_random ? 6 : time (0));

      is_initialized = TRUE;
      gagt_debug ("agt_rand", "[initialized]");
    }

  result = a + (rand () >> 2) % (b - a + 1);
  gagt_debug ("agt_rand", "a=%d, b=%d -> %d", a, b, result);
  return result;
}
