endEnt(double *r_ent, double *r_chisq, double *r_mean,
            double *r_montepicalc, double *r_scc)
{
  int i;


  scct1 = scct1 + scclast * sccu0;
  scct2 = scct2 * scct2;
  scc = totalc * scct3 - scct2;
  if (scc == 0.0)
    scc = -100000;
  else
    scc = (totalc * scct1 - scct2) / scc;


  cexp = totalc / (binary ? 2.0 : 256.0);
  for (i = 0; i < (binary ? 2 : 256); i++)
  { prob[i] = (double) ccount[i] / totalc;
    a = ccount[i] - cexp;
    chisq = chisq + (a * a) / cexp;
    datasum += ((double) i) * ccount[i];
  }


  for (i = 0; i < (binary ? 2 : 256); i++)
  { if (prob[i] > 0.0)
      ent += prob[i] * log2(1 / prob[i]);
  }


  montepi = 4.0 * (((double) inmont) / mcount);


  *r_ent = ent;
  *r_chisq = chisq;
  *r_mean = datasum / totalc;
  *r_montepicalc = montepi;
  *r_scc = scc;

}
