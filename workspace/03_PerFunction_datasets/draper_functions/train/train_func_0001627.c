initPlayers()
{

  KWin4Player* yellow = (KWin4Player*)createPlayer(1, mPlayedBy[Yellow], false);
  yellow->setUserId(Yellow);
  yellow->setName(Prefs::name1());
  addPlayer(yellow);
  setPlayedBy(Yellow,mPlayedBy[Yellow]);


  KWin4Player* red = (KWin4Player*)createPlayer(1, mPlayedBy[Red], false);
  red->setUserId(Red);
  red->setName(Prefs::name1());
  addPlayer(red);
  setPlayedBy(Red,mPlayedBy[Red]);
}
