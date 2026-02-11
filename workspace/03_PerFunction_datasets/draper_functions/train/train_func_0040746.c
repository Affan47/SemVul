errorOnReceive(int rc, const char* filename, CORBA::ULong lineno,
			   giopStream_Buffer* buf,CORBA::Boolean heldlock,
			   const char* message) {

  CORBA::ULong minor;
  CORBA::Boolean retry;

  notifyCommFailure(heldlock,minor,retry);
  if (rc == 0) {


    if (buf && buf->end != buf->start) {


      pd_strand->state(giopStrand::DYING);
    }
    retry = 0;
    minor = TRANSIENT_CallTimedout;
  }
  else {
    pd_strand->state(giopStrand::DYING);
  }
  if (buf) giopStream_Buffer::deleteBuffer(buf);

  CommFailure::_raise(minor,(CORBA::CompletionStatus)completion(),retry,
		      filename,lineno, message, pd_strand);

}
