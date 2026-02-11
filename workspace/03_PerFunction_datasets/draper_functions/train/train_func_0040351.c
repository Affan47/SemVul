check_block_fam(block_fam, blocks_num, seqs_num)
Block *block_fam[] ;
int   blocks_num, *seqs_num ;
{
   int i1, i2, i3, i4 ;


   if (block_fam[0]->number[(int) strlen(block_fam[0]->number)-1] != 'A')
      {
      fprintf(stderr,"Warning ! The name of the first block in family %s\n",
             block_fam[0]->number) ;
      fprintf(stderr,"does not end with an \"A\".\n") ;
      }


   for(i1=1; i1<blocks_num; i1++)
      if (block_fam[i1]->number[(int) strlen(block_fam[i1]->number)-1] -
          block_fam[i1-1]->number[(int) strlen(block_fam[i1-1]->number)-1]
          != 1)
         {
         fprintf(stderr,
            "Error ! Block %s is not the block expected to follow (by name)\n",
                block_fam[i1]->number ) ;
         fprintf(stderr,"block %s.\n", block_fam[i1-1]->number) ;
         return(ERROR) ;
	 }


   *seqs_num = block_fam[0]->num_sequences ;


   for(i1=1; i1<blocks_num; i1++)

      for(i2=0; i2<block_fam[i1]->num_sequences; i2++)
         {


         for(i3=0; i3<i1; i3++)
	    {
            for(i4=0; i4<block_fam[i3]->num_sequences &&
                      strcmp(block_fam[i1]->sequences[i2].name,
                             block_fam[i3]->sequences[i4].name) != 0; i4++) ;


            if (i4 < block_fam[i3]->num_sequences) break ;
            }


         if (i3 == i1) (*seqs_num)++ ;
         }

   for(i1=0; i1<blocks_num && block_fam[i1]->num_sequences == *seqs_num;
       i1++) ;
   if (i1 != blocks_num)
      fprintf(stderr,
          "Note - Not all sequences in family %s contain all the blocks.\n",
             block_fam[0]->number) ;

   return(OK) ;

}
