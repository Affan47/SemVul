notify_read_dir(int )
{
   int stat;
   if (!mainWin->m_notify) {
      return;
   }
   if (mainWin->m_commDebug) Pmsg1(000, "enter read_dir conn %i read_dir\n", m_conn);
   stat = m_sock->wait_data(0, 5000);
   if (stat > 0) {
      if (mainWin->m_commDebug) Pmsg2(000, "read_dir conn %i stat=%d\n", m_conn, stat);
      while (read() >= 0) {
         m_console->display_text(msg());
      }
   }
   if (mainWin->m_commDebug) Pmsg2(000, "exit read_dir conn %i stat=%d\n", m_conn, stat);
}
