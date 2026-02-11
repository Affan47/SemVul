QuitProgressMonitor(const char *task,
				      const magick_int64_t quantum,
				      const magick_uint64_t span,
				      ExceptionInfo *exception)
{
  ARG_NOT_USED(task);
  ARG_NOT_USED(quantum);
  ARG_NOT_USED(span);


  if (exception->severity < FatalErrorException)
    ThrowException(exception,MonitorFatalError,UserRequestedTerminationBySignal,0);

  return MagickFail;
}
