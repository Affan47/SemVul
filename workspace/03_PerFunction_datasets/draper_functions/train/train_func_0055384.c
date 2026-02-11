load_game_small(int num, char line[196], int *mytime)
{
  FILE *f = paths_savegame_fopen(num, "rb");
  if (f == NULL)
    {
      log_info("Couldn't quickload save game %d", num);
      return 0;
    }
  else
    {

      fseek(f, 4, SEEK_CUR);

      fread(line, 196, 1, f);
      line[195] = '\0';
      *mytime = read_lsb_int(f);
      fclose(f);

      return 1;
    }
}
