endGame(TABLE mode)
{
  setGameStatus(End);

  pView->endGame();


  KWin4Player *yellow=getPlayer(Yellow);
  KWin4Player *red=getPlayer(Red);
  switch(mode)
  {
    case TWin:  yellow->incWin();
                red->incLost();
    break;
    case TLost: yellow->incLost();
                red->incWin();
    break;
    case TRemis: yellow->incRemis();
                 red->incRemis();
    break;
    default:

       if (mMaxMove>0)
       {
          yellow->incBrk();
          red->incBrk();
       }
    break;
  }

}
