consensus(res, block)
int res;
Block *block;
{
   int s1, i, aaint;
   char aatemp[2];


   for (s1=0; s1 < block->num_sequences; s1++)
      for (i=0; i < block->width; i++)
      {
         aaint = aa_atob[ Results[res].aa[i]  ];
         if (aaint == block->sequences[s1].sequence[i] )
         {
            strncpy(aatemp, Results[res].aa+i, 1);
            if (aatemp[0] >= 97 && aatemp[0] <= 122)
            {
               aatemp[0] -= 32;
               strncpy(Results[res].aa+i, aatemp, 1);
            }
         }
      }

}
