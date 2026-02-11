_au_xt_eventEnqWorkProc(XtPointer data)
{
    PrivData       *priv = (PrivData *) data;

    if (setjmp(AuXtErrorJump))
	return True;

    AuHandleEvents(priv->aud);
    priv->eventEnqWorkProcActive = AuFalse;
    return True;
}
