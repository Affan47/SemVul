gnibbles_worm_grok_bonus (GnibblesWorm *worm)
{
  int i;

  if (gnibbles_boni_fake (boni, worm->xhead, worm->yhead)) {
    g_timeout_add (1, (GSourceFunc) gnibbles_worm_reverse, worm);
    play_sound ("reverse");
    return;
  }

  switch (board->walls[worm->xhead][worm->yhead] - 'A') {
    case BONUSREGULAR:
      boni->numleft--;
      worm->change += (boni->numboni - boni->numleft) * GROWFACTOR;
      worm->score += (boni->numboni - boni->numleft) * current_level;
      play_sound ("gobble");
      break;
    case BONUSDOUBLE:
      worm->score += (worm->length + worm->change) * current_level;
      worm->change += worm->length + worm->change;
      play_sound ("bonus");
      break;
    case BONUSHALF:
      if (worm->length + worm->change > 2) {
        worm->score += ((worm->length + worm->change) / 2) * current_level;
        gnibbles_worm_reduce_tail (worm,
                                  (g_list_length (worm->list)
                                  + worm->change) / 2);
        worm->change -= (g_list_length (worm->list) + worm->change) / 2;
        play_sound ("bonus");
      }
      break;
    case BONUSLIFE:
      worm->lives += 1;
      play_sound ("life");
      break;
    case BONUSREVERSE:
      for (i = 0; i < properties->numworms; i++)
        if (worm != worms[i])
          g_timeout_add (1, (GSourceFunc)
                         gnibbles_worm_reverse, worms[i]);
      play_sound ("reverse");
      break;
  }
}
