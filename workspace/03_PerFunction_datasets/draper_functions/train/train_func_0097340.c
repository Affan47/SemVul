control_event_signal(uintptr_t signal)
{
  const char *signal_string = NULL;

  if (!control_event_is_interesting(EVENT_SIGNAL))
    return 0;

  switch (signal) {
    case SIGHUP:
      signal_string = "RELOAD";
      break;
    case SIGUSR1:
      signal_string = "DUMP";
      break;
    case SIGUSR2:
      signal_string = "DEBUG";
      break;
    case SIGNEWNYM:
      signal_string = "NEWNYM";
      break;
    case SIGCLEARDNSCACHE:
      signal_string = "CLEARDNSCACHE";
      break;
    default:
      log_warn(LD_BUG, "Unrecognized signal %lu in control_event_signal",
               (unsigned long)signal);
      return -1;
  }

  send_control_event(EVENT_SIGNAL, ALL_FORMATS, "650 SIGNAL %s\r\n",
                     signal_string);
  return 0;
}
