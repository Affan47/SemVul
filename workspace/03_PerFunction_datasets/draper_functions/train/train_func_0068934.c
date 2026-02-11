InitDeviceComm()


{
    DRIVER_ERROR err = NO_ERROR;
    BOOL ErrorDisplayed = FALSE;
    BYTE temp;


    if( GetStatusInfo(&temp) == FALSE )
    {
        DBG1("InitDeviceComm:  No Status-Byte Available\n");
    }
    else IOMode.bStatus = TRUE;


    err = GetDeviceID(strDevID, DevIDBuffSize, TRUE);

    if ( err == NO_ERROR )
    {
        DBG1("InitDeviceComm:  DevID request successful\n");
        IOMode.bDevID = TRUE;
    }


    if ( IOMode.bStatus == TRUE )
    {


        if ( (err != NO_ERROR) && (PrinterIsAlive() == FALSE) )
        {

            while(PrinterIsAlive() == FALSE)
            {
                DBG1("PrinterIsAlive returned FALSE\n");
                ErrorDisplayed = TRUE;
                DisplayPrinterStatus(DISPLAY_NO_PRINTER_FOUND);

                if(BusyWait(500) == JOB_CANCELED)
                    return JOB_CANCELED;
            }
            if(ErrorDisplayed == TRUE)
            {
                DisplayPrinterStatus(DISPLAY_PRINTING);


                if(BusyWait(2000) == JOB_CANCELED)
                    return JOB_CANCELED;

                err = GetDeviceID(strDevID, DevIDBuffSize, TRUE);
                if ( err == NO_ERROR )
                {
                    DBG1("InitDeviceComm:  DevID request successful\n");
                    IOMode.bDevID = TRUE;
                }
            }
        }


    }

    if (err!=NO_ERROR)
    {
        DBG1("InitDeviceComm:  No DeviceID Available\n");
        return NO_ERROR;
    }

    err = DR->ParseDevIDString((const char*)strDevID, strModel, &VIPVersion, strPens);

    if (err!=NO_ERROR)
    {

        DBG1("InitDeviceComm:  The DevID string is invalid!\n");
        IOMode.bDevID=FALSE;
    }

    return NO_ERROR;
}
