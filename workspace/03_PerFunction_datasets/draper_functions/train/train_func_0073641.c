tack(void) {
      m_polling.lock();
      bool poll=polling;
      m_polling.unlock();
      if(poll)return;

      m_flag.lock();
      bool done=flag;
      flag=true;
      m_flag.unlock();

      if(done)return;


      sys_lock();
      clock_delay(clock, 0);
      sys_unlock();
    }
