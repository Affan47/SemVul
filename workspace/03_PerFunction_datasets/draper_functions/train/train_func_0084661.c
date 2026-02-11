reset()
{

  clearAllSprites();
  m_belongsTo = 0;
  nbArmies(1);
  createArmiesSprites();

  if (m_flag)
  {
    m_flag->hide();
    delete m_flag;
    m_flag = 0;
  }
}
