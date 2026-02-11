overflow(int u, int v)
{
      if (u > 0 && v > 0 && u + v < 0) return 1;
      if (u < 0 && v < 0 && u + v > 0) return 1;
      return 0;
}
