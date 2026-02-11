setBarFlagButton(const Player* player)
{


  if (player == 0)
  {
    if (currentPlayer()
        && currentPlayer()-> getFlag())
    {
      if (!m_goalAction->isVisible())
        m_goalAction->setVisible(true);
      m_goalAction-> setIcon(KIcon(currentPlayer()->getFlag()-> image(0)));
      m_goalAction-> setIconText(i18n("Goal"));
      m_barFlag-> setPixmap(currentPlayer()->getFlag()-> image(0));
      m_barFlag->show();
    }
  }
  else
  {
    if (player-> getFlag())
    {
      if (!m_goalAction->isVisible())
        m_goalAction->setVisible(true);
      m_goalAction-> setIcon(KIcon(player-> getFlag()-> image(0)));
      m_goalAction-> setIconText(i18n("Goal"));
      m_barFlag-> setPixmap(player->getFlag()-> image(0));
      m_barFlag->show();
    }
  }
  m_frame->setFocus();
}
