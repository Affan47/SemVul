printThreadBlockage(StgTSO *tso)
{
  switch (tso->why_blocked) {
#if defined(mingw32_HOST_OS)
    case BlockedOnDoProc:
    debugBelch("is blocked on proc (request: %u)", tso->block_info.async_result->reqID);
    break;
#endif
#if !defined(THREADED_RTS)
  case BlockedOnRead:
    debugBelch("is blocked on read from fd %d", (int)(tso->block_info.fd));
    break;
  case BlockedOnWrite:
    debugBelch("is blocked on write to fd %d", (int)(tso->block_info.fd));
    break;
  case BlockedOnDelay:
    debugBelch("is blocked until %ld", (long)(tso->block_info.target));
    break;
#endif
  case BlockedOnMVar:
    debugBelch("is blocked on an MVar @ %p", tso->block_info.closure);
    break;
  case BlockedOnBlackHole:
      debugBelch("is blocked on a black hole %p",
                 ((StgBlockingQueue*)tso->block_info.bh->bh));
    break;
  case BlockedOnMsgThrowTo:
    debugBelch("is blocked on a throwto message");
    break;
  case NotBlocked:
    debugBelch("is not blocked");
    break;
  case ThreadMigrating:
    debugBelch("is runnable, but not on the run queue");
    break;
  case BlockedOnCCall:
    debugBelch("is blocked on an external call");
    break;
  case BlockedOnCCall_Interruptible:
    debugBelch("is blocked on an external call (but may be interrupted)");
    break;
  case BlockedOnSTM:
    debugBelch("is blocked on an STM operation");
    break;
  default:
    barf("printThreadBlockage: strange tso->why_blocked: %d for TSO %d (%d)",
	 tso->why_blocked, tso->id, tso);
  }
}
