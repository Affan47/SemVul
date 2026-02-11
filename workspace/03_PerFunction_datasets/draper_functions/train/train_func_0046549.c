DBListPlayer (const char *style)
{
  int i;

  DBReadPlayer ();
  DBSortPlayer (style);
  for (i = 0; i < totalplayers; i++) {
    printf("%s %2.0f%% %d %d %d\n",
	playerdb[i].player,
	100.0*(playerdb[i].wins+((float)playerdb[i].draws/2))/
	 (playerdb[i].wins+playerdb[i].draws+playerdb[i].losses),
	playerdb[i].wins,
	playerdb[i].losses,
	playerdb[i].draws);
    if ((i+1) % 10 == 0) {printf("[Type a character to continue.]\n"); getchar();}
  }
}
