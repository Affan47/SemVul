save_hard(void)
{


  char skipbuf[10000];
  memset(skipbuf, 0, 10000);

  FILE *f = paths_dmodfile_fopen("hard.dat", "wb");
  if (!f)
    {
      perror("Couldn't save hard.dat");
      return;
    }


  int i = 0;
  for (i = 0; i < HARDNESS_NB_TILES; i++)
    {
      int j = 0;
      for (j = 0; j < 51; j++)
	fwrite(hmap.htile[i].x[j].y, 51, 1, f);
      fputc(hmap.htile[i].used, f);
      fwrite(skipbuf, 2, 1, f);
      fwrite(skipbuf, 4, 1, f);
    }
  for (i = 0; i < GFX_TILES_NB_SQUARES; i++)
    write_lsb_int(hmap.btile_default[i], f);
  fseek(f, (8000-GFX_TILES_NB_SQUARES)*4, SEEK_CUR);

  fclose(f);
}
