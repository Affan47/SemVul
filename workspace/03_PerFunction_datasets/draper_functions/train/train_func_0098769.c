permute(struct csa *csa)
{     int i, j, tmp;
      for (i = 1; i < AA; i++)
      {  j = RANDOM(i, AA);
         tmp = Parr[i];
         Parr[i] = Parr[j];
         Parr[j] = tmp;
      }
      return;
}
