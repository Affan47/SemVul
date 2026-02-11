disp_intron(FILE *f, gene *t, csw *sw)
{ int i,c,*s,*sb,*se;
  char genename[100];
  if (t->nintron <= 0) return;
  name(t,genename,1,sw);
  fprintf(f,"Intron from %s\n",genename);
  fprintf(f,"1   .   10    .   20    .   30    .   40    .   50\n");
  sb = t->eseq + t->intron;
  s = sb;
  se = sb + t->nintron;
  i = 0;
  while (s < se)
   { if ((c = *s++) < Adenine) break;
     fputc(cbase(c),f);
     if (++i >= 50)
      { fputc('\n',f);
        i = 0; }}
  if (i > 0) fputc('\n',f);
  fputc('\n',f);
  fprintf(f,"Intron Length: %d\n",t->nintron);
  fprintf(f,"Intron Insertion Position(%d-%d): ",t->intron,t->intron+1);
  s = sb - 5;
  for (i = 0; i < 5; i++) fputc(cbase(*s++),f);
  fprintf(f,"-Intron-");
  s = se;
  for (i = 0; i < 5; i++) fputc(cbase(*s++),f);
  fputc('\n',f);
  fputc('\n',f); }
