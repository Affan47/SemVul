argos(block)
Block *block;
{
   int width, pos, seq, seq1, seqs, diff[MAXROWS][MAXROWS];
   double total;

   width = block->sequences[0].length;
   if (width > EXTRA_LARGE_BUFF)
   {
        width = EXTRA_LARGE_BUFF;
	fprintf(stderr, "ERROR: Block %s is too wide (%d), truncated to %d\n",
		block->number, block->sequences[0].length, width);
   }
   seqs = block->num_sequences;
   if (seqs > MAXROWS)
   {
      seqs = MAXROWS;
	fprintf(stderr,"ERROR: Block %s is too deep (%d), truncated to %d sequences\n",
		block->number, block->num_sequences, seqs);
   }
   for (seq = 0; seq < seqs; seq++)
      for (seq1 = 0; seq1 < seqs; seq1++)
         diff[seq][seq1] = 0;
   for (seq = 0; seq < seqs; seq++)
      for (seq1 = 0; seq1 < seqs; seq1++)
         for (pos = 0; pos < width; pos++)
            if (block->residues[seq][pos] !=
                block->residues[seq1][pos])
                    diff[seq][seq1] = diff[seq][seq1] + 1;

   total = 0.0;
   for (seq = 0; seq < seqs; seq++)
      block->sequences[seq].weight = 0.0;
   for (seq = 0; seq < seqs; seq++)
      for (seq1 = 0; seq1 < seqs; seq1++)
      {
         block->sequences[seq].weight += (double) diff[seq][seq1];
         total += (double) diff[seq][seq1];
      }
   for (seq = 0; seq < seqs; seq++)
   {
      block->sequences[seq].weight /= total;
   }

}
