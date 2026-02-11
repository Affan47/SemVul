interrupt_action ()

{
  disableSig (SIGINT);
  stRmRegisteredFiles ();
  if ((nameCount - stThisTransaction.tr_seqno) > 1) {
    sprintf (stMessage, "\ncompletely stop saving (%d files unsaved) ?",
	     nameCount - stThisTransaction.tr_seqno);
    if (stAskConfirm (stMessage, "no")) {
      if (stThisTransaction.tr_done) {
	sprintf (stMessage, "\ntoo late, %s already saved", stThisTransaction.tr_fname);
	stLog (stMessage, ST_LOG_MSG);
	enableSig();
	return;
      }
      sprintf (stMessage, "%s not saved", stThisTransaction.tr_fname);
      stLog (stMessage, ST_LOG_MSG);
      enableSig();
      stCatchSigs ();
      af_cleanup ();
      longjmp (stThisTransaction.tr_env, 1);
    }
    else {
      sprintf (stMessage, "%s not saved", stThisTransaction.tr_fname);
      stLog (stMessage, ST_LOG_MSG);
      stExit (1);
    }
  }
  else {
    sprintf (stMessage, "\n%s %ssaved", stThisTransaction.tr_fname,
	     stThisTransaction.tr_done ? "already " : "not ");
    stLog (stMessage, ST_LOG_MSG);
    stExit (1);
  }
}
