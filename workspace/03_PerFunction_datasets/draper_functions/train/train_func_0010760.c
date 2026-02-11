sitecombcrunch (rawdata *rdta, cruncheddata *cdta)

  {
    int  i, sitei, j, sitej, k;
    boolean  tied;

    i = 0;
    cdta->alias[0] = cdta->alias[1];
    cdta->aliaswgt[0] = 0;

    for (j = 1; j <= rdta->sites; j++) {
      sitei = cdta->alias[i];
      sitej = cdta->alias[j];
      tied = (rdta->sitecat[sitei] == rdta->sitecat[sitej]);

      for (k = 1; tied && (k <= rdta->numsp); k++)
        tied = (rdta->y[k][sitei] == rdta->y[k][sitej]);

      if (tied) {
        cdta->aliaswgt[i] += rdta->wgt2[sitej];
        }
      else {
        if (cdta->aliaswgt[i] > 0) i++;
        cdta->aliaswgt[i] = rdta->wgt2[sitej];
        cdta->alias[i] = sitej;
        }
      }

    cdta->endsite = i;
    if (cdta->aliaswgt[i] > 0) cdta->endsite++;
  }
