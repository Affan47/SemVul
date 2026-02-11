find_blocks(nseq, seqs)
int nseq;
Sequence *seqs[MAXSEQ];
{
   struct blocks_list *blocks;
   Block *block;
   int length, s, pos, spos, width, firstpos;

   blocks = make_blist();

   length = seqs[0]->length;
   for (s=1; s<nseq; s++)
   {
      if (seqs[s]->length < length)
      {
         length = seqs[s]->length;
         fprintf(stderr,
             "WARNING: sequence segments are of different lengths\n");
         fprintf(stderr, "%s %d : %s %d\n",
   	     seqs[0]->name, seqs[0]->length, seqs[s]->name, seqs[s]->length);

      }
   }

   width = firstpos = 0;
   for (pos=0; pos < length; pos++)
   {
      spos = 0;
      for (s=0; s< nseq; s++)
         if (seqs[s]->sequence[pos] > 0 &&
             seqs[s]->sequence[pos] < 24 )
               spos++;
      if (spos == nseq) { width++; }

      if ( spos < nseq || (spos == nseq && width == MaxWidth) )
      {
         if (width >= MinWidth)

         {
            block = make_block(width, firstpos, nseq, seqs);
            insert_blist(blocks, block);
         }
         firstpos = pos + 1;
         width = 0;
      }
   }


   if (width >= MinWidth)

   {
      block = make_block(width, firstpos, nseq, seqs);
      insert_blist(blocks, block);
   }

   return(blocks);

}
