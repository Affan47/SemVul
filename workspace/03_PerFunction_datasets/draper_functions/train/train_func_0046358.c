moveArmiesAction()
{
  kDebug() << "AIPlayer::moveArmiesAction" << endl;
  QList<Country*> srcList = countries() ;
  if (srcList.size() == 0)
  {
    nextPlayerAction();
    return false;
  }
  uint which = Dice::roll(srcList.size()) - 1;
  Country* osrc =  srcList.at(which);

  if (osrc-> nbArmies() <= 1)
  {
    nextPlayerAction();
    return false;
  }

  QList<Country*> destList( m_world-> neighboursBelongingTo(*osrc, this) );

  if (destList.size() == 0)
  {
    nextPlayerAction();
    return false;
  }
  which = Dice::roll(destList.size()) - 1 ;

  Country* odest =  destList.at(which);
  m_src = osrc;
  m_dest = odest;

  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::WriteOnly);
  stream << QString("actionLButtonDown") << osrc->centralPoint();
  aiPlayerIO()->sendInput(stream,true);

  QByteArray buffer2;
  QDataStream stream2(&buffer2, QIODevice::WriteOnly);
  stream2 << QString("actionLButtonUp") << odest->centralPoint();
  aiPlayerIO()->sendInput(stream2,true);


  kDebug() << "AIPlayer ****************" << Player::name()  << " : moveAction : "  << osrc-> name() << " " << odest-> name() << endl;

  return true;
}
