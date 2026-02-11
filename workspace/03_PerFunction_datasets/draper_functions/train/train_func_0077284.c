screen_rank_map_sprites(int* rank)
{
  memset(rank, 0, MAX_SPRITES_EDITOR * sizeof(int));

  int r1 = 0;
  int already_checked[MAX_SPRITES_EDITOR+1];
  memset(already_checked, 0, sizeof(already_checked));
  for (r1 = 0; r1 < MAX_SPRITES_EDITOR; r1++)
    {
      int highest_sprite = 22000;
      rank[r1] = 0;

      int h1;
      for (h1 = 1; h1 <= MAX_SPRITES_EDITOR; h1++)
	{
	  if (already_checked[h1] == 0 && pam.sprite[h1].active)
	    {
	      int height;
	      if (pam.sprite[h1].que != 0)
		height = pam.sprite[h1].que;
	      else
		height = pam.sprite[h1].y;

	      if (height < highest_sprite)
		{
		  highest_sprite = height;
		  rank[r1] = h1;
		}
	    }
	}
      if (rank[r1] != 0)
	already_checked[rank[r1]] = 1;
    }
}
