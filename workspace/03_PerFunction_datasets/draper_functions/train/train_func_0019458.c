MagickSignalHandler(int signo)
{


  quit_signal_handler_call_count++;


  if (1 == quit_signal_handler_call_count)
    {
      if (MagickInitialized == InitInitialized)
	{


	  (void) SetMonitorHandler(QuitProgressMonitor);


	  PurgeTemporaryFiles();
	}


      SignalHandlerExit(signo);
    }
}
