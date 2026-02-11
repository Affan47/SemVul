SaveArrayKCluster(FILE* file, int k, const int* NodeMap)
{ int i, cluster;
  int* arrayindex = malloc(_columns*sizeof(int));
  if (!arrayindex) return 0;
  fputs("ARRAY\tGROUP\n", file);
  for (i=0; i<_columns; i++) arrayindex[i] = i;
  sort(_columns,_arrayorder,arrayindex);
  for (cluster = 0; cluster < k; cluster++)
  { for (i = 0; i < _columns; i++)
    { const int j = arrayindex[i];
      if (NodeMap[j]==cluster)
        fprintf(file, "%s\t%d\n", _arrayname[j], NodeMap[j]);
    }
  }
  free(arrayindex);
  return 1;
}
