run()
    {
      _fork.fork();
      if (_fork.child())
      {
        streambuf.redirectStdin();
        streambuf.closeWriteFd();
        try
        {
          _exec.exec();
        }
        catch (const SystemError&)
        {
          ::_exit(-1);
        }
      }

      streambuf.closeReadFd();
    }
