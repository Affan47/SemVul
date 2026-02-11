getclustermeans(int nclusters, int nrows, int ncolumns,
  double** data, int** mask, int clusterid[], double** cdata, int** cmask,
  int transpose)


{ int i, j, k;
  if (transpose==0)
  { for (i = 0; i < nclusters; i++)
    { for (j = 0; j < ncolumns; j++)
      { cmask[i][j] = 0;
        cdata[i][j] = 0.;
      }
    }
    for (k = 0; k < nrows; k++)
    { i = clusterid[k];
      for (j = 0; j < ncolumns; j++)
      { if (mask[k][j] != 0)
        { cdata[i][j]+=data[k][j];
          cmask[i][j]++;
        }
      }
    }
    for (i = 0; i < nclusters; i++)
    { for (j = 0; j < ncolumns; j++)
      { if (cmask[i][j]>0)
        { cdata[i][j] /= cmask[i][j];
          cmask[i][j] = 1;
        }
      }
    }
  }
  else
  { for (i = 0; i < nrows; i++)
    { for (j = 0; j < nclusters; j++)
      { cdata[i][j] = 0.;
        cmask[i][j] = 0;
      }
    }
    for (k = 0; k < ncolumns; k++)
    { i = clusterid[k];
      for (j = 0; j < nrows; j++)
      { if (mask[j][k] != 0)
        { cdata[j][i]+=data[j][k];
          cmask[j][i]++;
        }
      }
    }
    for (i = 0; i < nrows; i++)
    { for (j = 0; j < nclusters; j++)
      { if (cmask[i][j]>0)
        { cdata[i][j] /= cmask[i][j];
          cmask[i][j] = 1;
        }
      }
    }
  }
}
