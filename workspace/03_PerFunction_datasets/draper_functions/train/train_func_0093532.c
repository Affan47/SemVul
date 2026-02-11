aln_score(void)
{
  static short  *mat_xref, *matptr;
  static sint maxres;
  static sint  s1,s2,c1,c2;
  static sint    ngaps;
  static sint    i,l1,l2;
  static lint    score;
  static sint   matrix[NUMRES][NUMRES];


  matptr = blosum45mt;
  mat_xref = def_aa_xref;
  maxres = get_matrix(matptr, mat_xref, matrix, TRUE, 100);
  if (maxres == 0)
    {
       fprintf(stdout,"Error: matrix blosum30 not found\n");
       return;
    }

  score=0;
  for (s1=1;s1<=nseqs;s1++)
   {
    for (s2=1;s2<s1;s2++)
      {

        l1 = seqlen_array[s1];
        l2 = seqlen_array[s2];
        for (i=1;i<l1 && i<l2;i++)
          {
            c1 = seq_array[s1][i];
            c2 = seq_array[s2][i];
            if ((c1>=0) && (c1<=max_aa) && (c2>=0) && (c2<=max_aa))
                score += matrix[c1][c2];
          }

        ngaps = count_gaps(s1, s2, l1);

        score -= 100 * gap_open * ngaps;

      }
   }

  score /= 100;

  info("Alignment Score %d", (pint)score);

}
