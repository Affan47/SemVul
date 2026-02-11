VerifyPenInfo()
{

    DRIVER_ERROR err = NO_ERROR;

    if(IOMode.bDevID == FALSE)
        return err;

    ePen = NO_PEN;

    err = ParsePenInfo(ePen);
    ERRCHECK;

    while (ePen == NO_PEN)
    {
        err = ParsePenInfo (ePen);
        ERRCHECK;
        if (ePen == NO_PEN)
        {
            pSS->DisplayPrinterStatus (DISPLAY_NO_PENS);
            if (pSS->BusyWait (500) == JOB_CANCELED)
                return JOB_CANCELED;
        }

    }

    pSS->DisplayPrinterStatus (DISPLAY_PRINTING);

    return NO_ERROR;
}
