wait(unsigned long) {

    if(Thread::interrupted())
      throw Interrupted_Exception();

    Guard<Mutex> g(_lock);
    return true;

  }
