get_seq(fam, name, fdb, fout)
char *fam, *name;
FILE *fdb, *fout;
{
   Sequence *seq;
   char seqname[MAXNAME];


   seq = read_seq(fdb, name);
   if (seq == NULL)
   {
      printf ("Sequence %s not found\n", name);
   }
   else
   {
      sprintf(seqname, "%s %s", fam, name);
      strcpy(seq->name, seqname);
      output_sequence(seq, fout);
   }
}
