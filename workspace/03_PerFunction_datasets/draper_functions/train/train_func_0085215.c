startTimer()
{
   m_timer = new QTimer(this);
   QWidget::connect(m_timer, SIGNAL(timeout()), this, SLOT(poll_messages()));
   m_timer->start(mainWin->m_checkMessagesInterval*30000);
}
