writeweights()
{
  long j, k, l, m, n, o;

  j = 0;
  l = 1;
  if (interleaved)
    m = 60;
  else
    m = sites;
  do {
    if(m > sites)
      m = sites;
    n = 0;
    for (k = l - 1; k < m; k++) {
      for(o = 0 ; o < how_many[k] ; o++){
        if(oldweight[k]==0){
          fprintf(outweightfile, "0");
          j++;
        }
        else{
          if (weight[k-j] < 10)
            fprintf(outweightfile, "%c", (char)('0'+weight[k-j]));
          else
            fprintf(outweightfile, "%c", (char)('A'+weight[k-j]-10));
          n++;
          if (!interleaved && n > 1 && n % 60 == 1) {
            fprintf(outweightfile, "\n");
            if (n % 10 == 0 && n % 60 != 0)
              putc(' ', outweightfile);
          }
        }
      }
    }
    putc('\n', outweightfile);
    if (interleaved) {
      l += 60;
      m += 60;
    }
  } while (interleaved && l <= sites);
}
