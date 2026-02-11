dnadist_sitecombine(void)
{

  long i, j, k;
  boolean tied;

  i = 1;
  while (i < sites) {
    j = i + 1;
    tied = true;
    while (j <= sites && tied) {
      tied = (oldweight[alias[i - 1] - 1] == oldweight[alias[j - 1] - 1] &&
              category[alias[i - 1] - 1] == category[alias[j - 1] - 1]);
      k = 1;
      while (k <= spp && tied) {
        tied = (tied &&
            y[k - 1][alias[i - 1] - 1] == y[k - 1][alias[j - 1] - 1]);
        k++;
      }
      if (!tied)
        break;
      ally[alias[j - 1] - 1] = alias[i - 1];
      j++;
    }
    i = j;
  }
}
