player_setup_mode(void)
{
  char *items[] = {0,0,"Left player keys",
		   "Right player keys","Go back",0};
  while (1)
    {
      if (player_ishuman[1])
	items[0] = "Left Player: Keyboard";
      else
	items[0] = "Left Player: AI";
      if (player_ishuman[0])
	items[1] = "Right Player: Keyboard";
      else
	items[1] = "Right Player: AI";

      switch (select_mode("Player setup",items))
	{
	case 0:
	  player_ishuman[1] = 1 - player_ishuman[1];
	  if (player_ishuman[1])
	    player_sethuman(1);
	  else
	    player_setai(1);
	  break;
	case 1:
	  player_ishuman[0] = 1 - player_ishuman[0];
	  if (player_ishuman[0])
	    player_sethuman(0);
	  else
	    player_setai(0);
	  break;
	case 2:
	  player_keys_mode(1);
	  break;
	case 3:
	  player_keys_mode(0);
	  break;
	default:
	  return;
	}
    }
}
