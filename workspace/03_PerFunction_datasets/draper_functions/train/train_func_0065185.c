getdelta(int x, int y, int x2, int y2)
  {
    int ans = 0;
    if (x2 == x) return ans;
    if (y2 > y) {
      ans = 1;
      double slope = (y2-y) / double(x2-x);
      if (fabs(slope) > 1.0)
        ans = 0;
    }
    return ans;
  }
