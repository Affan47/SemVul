EmbeddedZipArchiveFactory_close(int fd)
    {
        if (fd == EMBED_IO_BAD_FILE_HANDLE)
        {

            return -1;
        }

        EmbeddedFileData & curEmbeddedFileData = getEmbeddedFileDataByIndex(fd);

        if(curEmbeddedFileData.isFileOpened == false)
        {

           return -1;
        }
        else
        {

            curEmbeddedFileData.isFileOpened = false;
            curEmbeddedFileData.curPos = 0;
            return 0;
        }

    }
