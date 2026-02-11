stop(unsigned int timeout) {
      if(!isrunning)return true;
      int timmy=(timeout/10);
      bool checktimeout=(timeout>0);

      keeprunning=false;

      while(isrunning) {
        usleep(10);
        if(checktimeout && (timmy--<10))break;
      }
      return (!isrunning);
  }
