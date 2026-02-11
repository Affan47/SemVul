__setup_contab(void)
{
 register int32 i, j;

 __contabwsiz = 400;
 __contab = (word32 *) __my_malloc(__contabwsiz*sizeof(word32));

 for (i = 0; i < 4; i++) __contab[i] = ALL1W;

 __contab[4] = 0;
 __contab[5] = 1;

 __contab[6] = 1;
 __contab[7] = 1;

 __contab[8] = 0;
 __contab[9] = ALL1W;

 __contab[10] = ALL1W;
 __contab[11] = ALL1W;

 for (i = 12, j = 0; i <= 12 + 2*128; i += 2, j++)
  {
   __contab[i] = j;
   __contab[i + 1] = 0;
  }


 __opempty_contabi = 270;
 __contab[270] = ' ';
 __contab[271] = 0;
 __contabwi = 272;

 __contab_hash = (struct contab_info_t **)
  __my_malloc(HASHTABSIZ*sizeof(struct contab_info_t *));
 memset(__contab_hash, 0, HASHTABSIZ*sizeof(struct contab_info_t *));

}
