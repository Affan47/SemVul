setDeal()
{
   int pl, s, nplayer, c;
  char *pc;
  ushort msuit[4];

  pc = szDeal;
  memset(mPlayerSuit,0,4*4*sizeof(ushort));
  memset(msuit,0,4*sizeof(ushort));
  pl = ePLAYER_WEST;
  s = eSUIT_SPADE;
  nplayer = 1;
  for(;;)
  { if(nplayer > 4)
    { sprintf(szErrMsg,"*** error: deal too many players\n");
      return false;
    }
    else if(pc[0] == '\0')
      break;
    else if(pc[0] == ' ')
    {
      pl = ((pl+1) & 3);
      s = eSUIT_SPADE;
      nplayer++;
    }
    else if(*pc == '.')
    {
      s++;
      if(s > eSUIT_CLUB)
      { sprintf(szErrMsg,"*** error: deal too many suits\n");
        return false;
      }
    }
    else
    { if(bitCount(mPlayerSuit[pl][s]) >= 13)
      { sprintf(szErrMsg,"*** error: more than 13 cards in suit at line %d\n",
                nLine);
        return false;
      }
      c = getCard(pc[0]);
      if(c == eCARD_NONE)
      { sprintf(szErrMsg,"*** error: invalid deal card %c line %d\n",
                pc[0],nLine);
        return false;
      }
      if(isBit(mPlayerSuit[pl][s],c))
      { sprintf(szErrMsg,"*** error: duplicate card %c player %c\n",
                chCARD[c],chPLAYER[pl]);
        return false;
      }
      if(isBit(msuit[s],c))
      { sprintf(szErrMsg,"*** error: duplicate card %c in more than one hand\n",
                chCARD[c]);
        return false;
      }
      setBit(msuit[s],c);
      setBit(mPlayerSuit[pl][s],c);
    }
    pc++;
  }


  if(   (nPlayerCard(0) != nPlayerCard(1))
     || (nPlayerCard(0) != nPlayerCard(2))
     || (nPlayerCard(0) != nPlayerCard(3)))
  { sprintf(szErrMsg,"*** error: different number of cards in hands line %d\n",
            nLine);
    return false;
  }


  if(setPlayed() == false)
    return false;

  return true;

}
