VirtualRun()
  {
    if(_real_time) {
      return -1;
    }

    qint64 next = Run();


    QThreadPool::globalInstance()->waitForDone();

    QCoreApplication::processEvents();
    QCoreApplication::sendPostedEvents();

    return next;
  }
