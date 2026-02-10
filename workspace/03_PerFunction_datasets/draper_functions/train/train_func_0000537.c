moveDone()
{

   m_view->setNormalCursor();
   emit statusMessage (QString(""), false);
   m_activity = Idle;
   setAction (HINT, true);
   m_fullSpeed = Prefs::animationNone();
   m_view->hidePopup();
   if (m_interrupting) {
      m_interrupting = false;
      m_waitingState = ComputerToMove;
   }
}
