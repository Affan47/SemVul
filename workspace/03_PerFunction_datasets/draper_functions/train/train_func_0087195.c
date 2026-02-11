VerifyPenInfo()
{
    DRIVER_ERROR err=NO_ERROR;

    if(IOMode.bDevID == FALSE)
        return err;

    err = ParsePenInfo(ePen);
    ERRCHECK;


    if (ePen == BOTH_PENS || ePen == MDL_BOTH || ePen == COLOR_PEN || ePen == BLACK_PEN)
        return NO_ERROR;

DBG1("Apollo2xxx::VerifyPenInfo(): ePen is not BOTH_PENS, MDL_BOTH, COLOR_PEN, or BLACK_PEN\n");


    while ( (ePen != BOTH_PENS) && (ePen != MDL_BOTH) && (ePen != COLOR_PEN) && (ePen != BLACK_PEN))
    {
DBG1("Apollo2xxx::VerifyPenInfo(): in while loop\n");

        switch (ePen)
        {
            case MDL_PEN:

                pSS->DisplayPrinterStatus(DISPLAY_NO_COLOR_PEN);
                break;
            case NO_PEN:

            default:
                pSS->DisplayPrinterStatus(DISPLAY_NO_PENS);
                break;
        }

        if (pSS->BusyWait(500) == JOB_CANCELED)
            return JOB_CANCELED;

        err =  ParsePenInfo(ePen);
        ERRCHECK;
    }

    pSS->DisplayPrinterStatus(DISPLAY_PRINTING);

    return NO_ERROR;

}
