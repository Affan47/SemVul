defense(unsigned int nb)
{
  kDebug();

  if (!m_firstCountry)
     return;

  m_secondCountry-> owner()-> setNbDefense(nb);

  QPixmap pmA = m_firstCountry-> owner()->getFlag()->image(0);
  QPixmap pmD = m_secondCountry-> owner()->getFlag()->image(0);

  KMessageParts messageParts;
  messageParts << I18N_NOOP("Battle ongoing.");


  broadcastChangeItem(messageParts, ID_STATUS_MSG2, false);

  if (m_firstCountry-> owner() && m_firstCountry-> owner()-> getFlag())
  {
    if (!m_goalAction->isVisible())
      m_goalAction->setVisible(true);
    m_goalAction-> setIcon(KIcon(m_firstCountry-> owner()->getFlag()-> image(0)));
    m_goalAction-> setIconText(i18n("Goal"));
    m_barFlag-> setPixmap(m_firstCountry-> owner()->getFlag()-> image(0));
  }
  if (m_automaton->isAdmin())
  {
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    m_automaton->sendMessage(buffer,InitCombatMovement);
    m_automaton->state(GameLogic::GameAutomaton::FIGHT_BRING);
  }
}
