redrawLine(CliPlayerList *pl, int playerNum)  {
  CliPlayer  *p;
  ButEnv  *env;
  int  bw, lastPlayer, physFontH;
  char  state[2];

  assert(MAGIC(pl));
  if (pl->win)  {
    p = &pl->players[playerNum];
    getListEl(pl, playerNum, &pl->data->cmdBuild);
    if (p->state == cliPlayer_noPlayer)  {
      if (p->match)  {
	but_destroy(p->match);
	p->match = NULL;
      }
      if (playerNum == butList_len(pl->list) - 1)  {
	for (lastPlayer = playerNum - 1;
	     ((lastPlayer >= 0) &&
	      (pl->players[lastPlayer].state == cliPlayer_noPlayer));
	     --lastPlayer);
	butList_setLen(pl->list, lastPlayer + 1);
	butCan_resizeWin(pl->swin->win, 0, (lastPlayer + 1) *
			 butEnv_fontH(pl->data->cg->env, 0) +
			 butEnv_stdBw(pl->data->cg->env) * 2, TRUE);
      }
    } else  {
      if (playerNum >= butList_len(pl->list))  {
	butList_setLen(pl->list, playerNum + 1);
	butCan_resizeWin(pl->swin->win, 0, butList_len(pl->list) *
			 butEnv_fontH(pl->data->cg->env, 0) +
			 butEnv_stdBw(pl->data->cg->env) * 2, TRUE);
      }
      if (p->match == NULL)  {
	if ((p->state != cliPlayer_closed) && (p->gameIn == -1))  {
	  state[0] = "?XO! "[p->state];
	  state[1] = '\0';
	  p->match = butCt_create(matchPressed, pl, pl->swin->win, 3,
				  BUT_DRAWABLE|BUT_PRESSABLE, state);
	  env = pl->data->cg->env;
	  physFontH = butEnv_fontH(env, 0);
	  bw = butEnv_stdBw(env);
	  but_resize(p->match, bw + physFontH * 7,
		     bw + physFontH * playerNum,
		     physFontH * 2, physFontH);
	}
      } else  {
	if ((p->state == cliPlayer_closed) || (p->gameIn != -1))  {
	  but_destroy(p->match);
	  p->match = NULL;
	} else  {
	  state[0] = "?XO! "[p->state];
	  state[1] = '\0';
	  butCt_setText(p->match, state);
	}
      }
    }
    butList_changeLine(pl->list, playerNum,
		       str_chars(&pl->data->cmdBuild));
  }
}
