loadStoredPrint(const char *filename)
{
    OFCondition status = EC_IllegalCall;
    DcmFileFormat *fileformat = NULL;
    DVPSStoredPrint *print = new DVPSStoredPrint(getDefaultPrintIllumination(), getDefaultPrintReflection());
    if (print==NULL)
    {
        DCMPSTAT_LOGFILE("Load stored print from file failed: memory exhausted");
        return EC_MemoryExhausted;
    }

    if ((status = DVPSHelper::loadFileFormat(filename, fileformat)) == EC_Normal)
    {
        if (fileformat)
        {
            DcmDataset *dataset = fileformat->getDataset();
            if (dataset)
            {
                if (EC_Normal == (status = print->read(*dataset)))
                {
                    delete pPrint;
                    pPrint = print;
                    clearFilmSessionSettings();
                }
            } else status = EC_CorruptedData;
            delete fileformat;
        } else status = EC_IllegalCall;
        if (status != EC_Normal)
            DCMPSTAT_LOGFILE("Load stored print from file failed: invalid data structures");
    } else
        DCMPSTAT_LOGFILE("Load stored print from file failed: could not read fileformat");
    if (status != EC_Normal)
    {
        delete print;
    }
    return status;
}
