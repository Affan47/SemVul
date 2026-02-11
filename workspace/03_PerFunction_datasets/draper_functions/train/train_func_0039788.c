DBWritePlayer (void)
{
   int i;
   float result1;
   int result2;
   FILE *wfp;
   DBSortPlayer ("reverse");
   if ((wfp = fopen(PLAYERFILE,"w")) != NULL) {
     for (i = 0; i < totalplayers; i++) {
        result1 =
  	  100.0*(playerdb[i].wins+((float)playerdb[i].draws/2))/
	   (playerdb[i].wins+playerdb[i].draws+playerdb[i].losses),
	result2 = (int) result1;
        fprintf(wfp,"%s %d %d %d\n",
	  playerdb[i].player,
          playerdb[i].wins,
          playerdb[i].losses,
	  playerdb[i].draws);
     }
   }
   fclose(wfp);
}
