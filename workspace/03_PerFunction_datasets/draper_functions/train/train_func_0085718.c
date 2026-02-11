terminate()
{
   foreach(DirComm* dircomm,  m_dircommHash) {
      dircomm->terminate();
   }
   m_console->stopTimer();
}
