EndJob ()
{
    DRIVER_ERROR    err = NO_ERROR;

	err = thePrinter->Send((const BYTE*)JrEndSessionSeq, sizeof(JrEndSessionSeq));
	ERRCHECK;

	err = thePrinter->Send((const BYTE*)ccpPJLExitSeq, sizeof(ccpPJLExitSeq));
	ERRCHECK;

    return err;
}
