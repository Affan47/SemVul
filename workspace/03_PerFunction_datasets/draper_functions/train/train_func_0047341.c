clear_save_records (void)
{
  memset (saverec, 0, 10 * sizeof (saved_game));

  if (x10sav) {
    unsigned int i;
    for (i = 0; i < 10; i++) {
      sprintf (saverec[i].name, "LVL%u", (1 + i) * 10);
      saverec[i].level = (1 + i) * 10 - 1;
      saverec[i].points[0] = saverec[i].points[1] = saverec[i].points[2] =
	saverec[i].points[3] = (1 + i) * 1000;
      saverec[i].lifes[0] = saverec[i].lifes[1] = saverec[i].lifes[2] =
	saverec[i].lifes[3] = 9;
      empty_gameid (saverec[i].gid);
      saverec[i].used = 1;
    }
  }
}
