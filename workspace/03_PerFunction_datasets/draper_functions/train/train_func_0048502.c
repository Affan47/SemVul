unplayCard()
{


  int player, suit, card;

  if(nPlayed == 0)
  { sprintf(szErrMsg,"*** error: no cards to unplay in giblibPlayCard()\n");
    return false;
  }

  nPlayed--;
  player = PlayerPlayed[nPlayed];
  suit   = SuitPlayed[nPlayed];
  card   = CardPlayed[nPlayed];


  setBit(mPlayerSuit[player][suit],card);

  nTrickCard = ((nTrickCard -1) & 3);
  if(nTrickCard == 3)
  { nTrick--;
    if(WinningPlayer[nTrick] & 1)
      nTrickSN--;
    else
      nTrickWE--;
    TrickStart = 4 * nTrick;
    SuitLed = SuitPlayed[TrickStart];
    Leader  = PlayerPlayed[TrickStart];
  }
  Player = PlayerPlayed[nPlayed];

  return true;

}
