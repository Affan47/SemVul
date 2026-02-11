readline()
{


  int status = 0;
  QByteArray prompt = this->prompt;
  QByteArray ba;
  mutex.unlock();
  ba = rtty_readline(prompt.constData());
  mutex.lock();
  switch (rtty_status)
    {
    case RttyOk:
      emit q->ttyInput(ba);
      break;
    case RttyEof:
      emit q->ttyEndOfFile();
    case RttyAbort:

      clearerr(stdin);
      int fd = fileno(stdin);
      if (wait_for_input(1, &fd, false) >= 0)
        fgetc(stdin);
      break;
    }
}
