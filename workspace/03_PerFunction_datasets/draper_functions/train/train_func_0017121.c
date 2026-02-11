write_pros()
{
  FILE *out;
  char *ctemp, filename[FNAMELEN];
  int i, j, min, max, imin, imax;


  imin = imax = max = -1; min = 30000;
  for (i=0; i<NumSeqs; i++)
  {
      if (Len[i] < min) {min = Len[i]; imin = i;}
      if (Len[i] > max) {max = Len[i]; imax = i;}
  }

  if (strlen(Batch_Filename) != 0)
  {
     filename[0] = '\0';
     strncat(filename, Batch_Filename+Batsplit->dir_len,
             Batsplit->name_len);
     filename[Batsplit->name_len] = '\0';
     strcat(filename, ".motifj.pros");
  }
  else
     strcpy(filename, "motifj.pros");
  if ( (out=fopen(filename, "w+b")) == NULL)
  {
     printf("\nUnable to open file %s", filename);
  }
  else
  {
     for (i=0; i<NumSeqs; i++)
     {
        fprintf(out, ">%s %d", Seqname[i], Len[i]);
        if (i == imin)      fprintf(out, " MINIMUM\n");
        else if (i == imax) fprintf(out, " MAXIMUM\n");
             else           fprintf(out, "\n");
        for (j=0; j<Len[i]; j++)
        {
	   ctemp = num_to_aachar(Seq[i][j]);
	   fprintf(out, "%1s", ctemp);
	   if ( ((j+1) % 80) == 0) fprintf(out, "\n");
        }
        fprintf(out, "\n");
      }
      fclose(out);
   }
}
