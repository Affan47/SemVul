oneArrived(AnimSprite* sprite)
{
  m_numberArrived++;
  kDebug() << (void*)sprite << ":" << m_numberArrived << " on " << AnimSpritesList<AnimSprite>::size();


  if (sprite != 0)
  {
    sprite->arrival();
  }
  if (m_numberArrived == (unsigned int)AnimSpritesList<AnimSprite>::size())
  {
    emit arrived(this);
    m_numberArrived = 0;
  }
}
