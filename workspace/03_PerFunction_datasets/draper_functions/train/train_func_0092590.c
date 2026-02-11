loadFile(const char *file_name,
                                        const E_FileReadMode readMode,
                                        const E_TransferSyntax xfer)
{
    OFCondition cond;

    delete dfile;
    current_file = "";
    dfile = new DcmFileFormat();
    dset = dfile->getDataset();


    OFLOG_INFO(mdfdsmanLogger, "Loading file into dataset manager: " << file_name);
    cond = dfile->loadFile(file_name, xfer, EGL_noChange, DCM_MaxReadLength, readMode);

    if (cond.bad())
    {
        dset = NULL;
    }

    else
    {

        OFLOG_INFO(mdfdsmanLogger, "Getting dataset from loaded file: " << file_name);
        dset=dfile->getDataset();


        dset->loadAllDataIntoMemory();

        current_file = file_name;
    }
    return cond;
}
