slotTurn(QDataStream &in, bool turn)
{
  QByteArray buffer;
  QDataStream out(&buffer,QIODevice::WriteOnly);


  if (turn)
  {


    MoveResult result = think(in,out,false);
    int id            = KGameMessage::IdPlayerInput;
    proc.sendSystemMessage(out,id,0);
    sendValue(result.value, mCurMoveNo);


  }
}
